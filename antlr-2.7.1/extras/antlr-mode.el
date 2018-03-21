;;; antlr-mode.el --- Major mode for ANTLR grammar files

;; Copyright (C) 1999 SAP AG
;;
;; Author: Christoph.Wedler@sap-ag.de
;; Version: $Id: antlr-mode.el,v 1.0 1999/08/10 17:29:26 wedler Exp $
;; Platform: XEmacs-20.4+ or Emacs-20.3+, Unix or NT, cc-mode-5.20+
;; Status: beta

;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 2, or (at your option)
;; any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program; if not, write to the Free Software
;; Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

;;; Commentary:

;; Major mode for editing ANTLR grammar files, i.e., files ending with `.g'.
;; ANTLR is ANother Tool for Language Recognition (an excellent alternative to
;; lex/yacc), see <http://www.ANTLR.org> and <news:comp.compilers.tools.pccts>.

;; Variable `antlr-language' is set according to the language in actions and
;; semantic predicates of the grammar (see ANTLR's file option "language").
;; The supported languages are "Java" (java-mode) and "Cpp" (c++-mode).  This
;; package uses features of the Emacs package cc-mode.

;; This package provides the following features:
;;  * Indentation for the current line (TAB) and selected region (C-M-\).
;;  * Syntax coloring (via font-lock) with language dependend coloring.
;;  * Support for imenu/speedbar: menu "Rules" (Parser, Lexer, TreeParser).
;;  * Direct move to previous/next rule, beginning/end of rule body etc.

;; INDENTATION.  This package supports ANTLR's (intended) indentation style
;; which is based on a simple paren/brace/bracket depth-level calculation, see
;; `antlr-indent-line'.  The indentation engine of cc-mode is only used inside
;; block comments (it is not easy to use it for actions, esp if they come early
;; in the rule body).  By default, this package uses TABs for a basic offset of
;; 4 to be consistent to both ANTLR's conventions (TABs usage) and the
;; `c-indentation-style' "java" which sets `c-basic-offset' to 4, see
;; `antlr-tab-offset-alist'.

;; SYNTAX COLORING comes in three phases.  First, comments and strings are
;; highlighted.  Second, the grammar code is highlighted according to
;; `antlr-font-lock-additional-keywords' (rule refs: dark blue, token refs:
;; dark deep pink, definition: ditto+bold).  Third, actions, semantic
;; predicates and arguments are highlighted according to the usual font-lock
;; keywords of `antlr-language', see also `antlr-font-lock-maximum-decoration'.
;; We define special font-lock faces for the grammar code to allow you to
;; distinguish ANTLR keywords from Java/C++ keywords.

;;; Installation:

;; Put this file into your load-path and the following into your ~/.emacs:
;;   (autoload 'antlr-mode "antlr-mode" nil t)
;;   (push '("\\.g\\'" . antlr-mode) auto-mode-alist)
;;   (add-hook 'speedbar-load-hook  ; would be too late in antlr-mode.el
;;	       (lambda () (speedbar-add-supported-extension ".g")))

;; If you edit ANTLR's source files, you might also want to use
;;   (autoload 'antlr-set-tabs "antlr-mode")
;;   (add-hook 'java-mode-hook 'antlr-set-tabs)

;;; Code:

(provide 'antlr-mode)
(require 'cl)				; Emacs
(require 'easymenu)			; Emacs
(eval-when-compile (require 'cc-mode))	; shut up most warnings
;;(eval-when-compile (require 'imenu))	; missing autoload in imenu

(eval-and-compile
  (unless (fboundp 'with-syntax-table)	; from help.el (XEmacs-21.1)
    (defmacro with-syntax-table (syntab &rest body)
      `(let ((stab (syntax-table)))
	 (unwind-protect
	     (progn (set-syntax-table (copy-syntax-table ,syntab)) ,@body)
	   (set-syntax-table stab)))))
  (if (string-match "XEmacs" emacs-version)
      (defalias 'antlr-scan-sexps 'scan-sexps)
    (defalias 'antlr-scan-sexps 'antlr-scan-sexps-internal))
  (if (and (fboundp 'buffer-syntactic-context)
	   (fboundp 'buffer-syntactic-context-depth))
      (progn
	(defalias 'antlr-invalidate-context-cache 'antlr-xemacs-bug-workaround)
	(defalias 'antlr-syntactic-context 'antlr-fast-syntactic-context))
    (defalias 'antlr-invalidate-context-cache 'ignore)
    (defalias 'antlr-syntactic-context 'antlr-slow-syntactic-context)))



;;;;##########################################################################
;;;;  Variables
;;;;##########################################################################


;;;===========================================================================
;;;  Controlling ANTLR's code generator (language option)
;;;===========================================================================

(defvar antlr-language nil
  "Major mode corresponding to ANTLR's \"language\" option.
Set via `antlr-language-alist'.  The only useful place to change this
buffer-local variable yourself is in `antlr-mode-hook' or in the \"local
variable list\" near the end of the file, see
`enable-local-variables'.")

(defvar antlr-language-alist
  '((java-mode
     ("Java" nil "Java")
     ((list)				; nil won't work (would use level-3)
      java-font-lock-keywords-1 java-font-lock-keywords-2
      java-font-lock-keywords-3))
    (c++-mode
     ("C++" "Cpp")
     ((list)				; nil won't work (would use level-3)
      c++-font-lock-keywords-1 c++-font-lock-keywords-2
      c++-font-lock-keywords-3)))
  "List of ANTLR's supported languages.
Each element in this list looks like
  (MAJOR-MODE (MODELINE-STRING OPTION-VALUE ...) KEYWORDS)

MAJOR-MODE is the major mode of the code in the grammar's actions.
MODELINE-STRING is also displayed in the modeline next to \"Antlr\".
KEYWORDS are the font-lock keywords according to `font-lock-defaults'
used for the code in the grammar's actions and semantic predicates, see
`antlr-font-lock-maximum-decoration'.

MAJOR-MODE is the value of `antlr-language' if the first regexp group
matched by REGEXP in `antlr-language-limit-n-regexp' is one of the
OPTION-VALUEs.  An OPTION-VALUE of nil denotes the fallback element.")

(defvar antlr-language-limit-n-regexp
  '(3000 . "language[ \t]+=[ \t]*\"\\([A-Z][A-Za-z_]*\\)\"")
  "Used to set a reasonable value for `antlr-language'.
Looks like (LIMIT . REGEXP).  Search for REGEXP from the beginning of
the buffer to LIMIT to set the language according to
`antlr-language-alist'.")


;;;===========================================================================
;;;  Indent/Tabs
;;;===========================================================================

(defvar antlr-indent-comment 'tab
  "*Non-nil, if the indentation should touch lines in block comments.
If nil, no continuation line of a block comment is changed.  If t, they
are changed according to `c-indentation-line'.  When not nil and not t,
they are only changed by \\[antlr-indent-command].")

(defvar antlr-tab-offset-alist
  '((antlr-mode nil 4 t)
    (java-mode "antlr" 4 t))
  "Alist to determine whether to use ANTLR's convention for TABs.
Each element looks like (MAJOR-MODE REGEXP TAB-WIDTH INDENT-TABS-MODE).
The first element whose MAJOR-MODE is nil or equal to `major-mode' and
whose REGEXP is nil or matches `buffer-file-name' is used to set
`tab-width' and `indent-tabs-mode'.  This is useful to support both
ANTLR's and Java's indentation styles.  Used by `antlr-set-tabs'.")

(defvar antlr-indent-item-regexp
  "[]}):;|&]\\|default[ \t]*:\\|case[ \t]+\\('\\\\?.'\\|[0-9]+\\|[A-Za-z_][A-Za-z_0-9]*\\)[ \t]*:" ; & is local ANTLR extension
  "Regexp matching lines which should be indented by one TAB less.
See command \\[antlr-indent-command].")


;;;===========================================================================
;;;  Menu
;;;===========================================================================

(defvar antlr-imenu-name t
  "*Non-nil, if a \"Labels\" menu should be added to the menubar.
If it is a string, it is used instead \"Labels\".  Requires package
imenu.")

(defvar antlr-mode-map
  (let ((map (make-sparse-keymap)))
    (define-key map "\t" 'antlr-indent-command)
    (define-key map "\e\C-a" 'antlr-beginning-of-rule)
    (define-key map "\e\C-e" 'antlr-end-of-rule)
    (define-key map "\C-c\C-a" 'antlr-beginning-of-body)
    (define-key map "\C-c\C-e" 'antlr-end-of-body)
    (define-key map "\C-c\C-f" 'c-forward-into-nomenclature)
    (define-key map "\C-c\C-b" 'c-backward-into-nomenclature)
    ;; I'm too lazy to define my own:
    (define-key map "\ea" 'c-beginning-of-statement)
    (define-key map "\ee" 'c-end-of-statement)
    map)
  "Keymap used in `antlr-mode' buffers.")

(easy-menu-define antlr-mode-menu
		  antlr-mode-map
		  "Major mode menu."
		  '("Antlr"
		    ["Indent Line" antlr-indent-command
		     :active (not buffer-read-only)]
		    ["Indent for Comment" indent-for-comment
		     :active (not buffer-read-only)]
		    ["Backward Rule" antlr-beginning-of-rule t]
		    ["Forward Rule" antlr-end-of-rule t]
		    ["Start of Rule Body" antlr-beginning-of-body
		     :active (antlr-inside-rule-p)]
		    ["End of Rule Body" antlr-end-of-body
		     :active (antlr-inside-rule-p)]
		    "---"
		    ["Backward Statement" c-beginning-of-statement t]
		    ["Forward Statement" c-end-of-statement t]
		    ["Backward Into Nomencl." c-backward-into-nomenclature t]
		    ["Forward Into Nomencl." c-forward-into-nomenclature t]))


;;;===========================================================================
;;;  font-lock
;;;===========================================================================

(defvar antlr-font-lock-maximum-decoration 'inherit
  "*The maximum decoration level for fontifying actions.
Value `none' means, do not fontify actions, just normal grammar code
according to `antlr-font-lock-additional-keywords'.  Value `inherit'
means, use value of `font-lock-maximum-decoration'.  Any other value is
interpreted as in `font-lock-maximum-decoration' with no level-0
fontification, see `antlr-language-alist'.

While calculating the decoration level for actions, `major-mode' is
bound to `antlr-language'.  For example, with value
  ((java-mode . 2) (c++-mode . 0))
Java actions are fontified with level 2 and C++ actions are not
fontified at all.")

(defvar antlr-font-lock-default-face 'antlr-font-lock-default-face)
(defface antlr-font-lock-default-face
  nil
  "ANTLR keywords.")

(defvar antlr-font-lock-keyword-face 'antlr-font-lock-keyword-face)
(defface antlr-font-lock-keyword-face
  '((((class color) (background light)) (:foreground "black" :bold t)))
  "ANTLR keywords.")

(defvar antlr-font-lock-ruledef-face 'antlr-font-lock-ruledef-face)
(defface antlr-font-lock-ruledef-face
  '((((class color) (background light)) (:foreground "blue" :bold t)))
  "ANTLR rule references (definition).")

(defvar antlr-font-lock-tokendef-face 'antlr-font-lock-tokendef-face)
(defface antlr-font-lock-tokendef-face
  '((((class color) (background light)) (:foreground "DeepPink3" :bold t)))
  "ANTLR token references (definition).")

(defvar antlr-font-lock-ruleref-face 'antlr-font-lock-ruleref-face)
(defface antlr-font-lock-ruleref-face
  '((((class color) (background light)) (:foreground "blue4")))
  "ANTLR rule references (usage).")

(defvar antlr-font-lock-tokenref-face 'antlr-font-lock-tokenref-face)
(defface antlr-font-lock-tokenref-face
  '((((class color) (background light)) (:foreground "DeepPink4")))
  "ANTLR token references (usage).")

(defvar antlr-font-lock-literal-face 'antlr-font-lock-literal-face)
(defface antlr-font-lock-literal-face
  '((((class color) (background light)) (:foreground "red4" :bold t)))
  "ANTLR literal tokens consisting merely of letter-like characters.")

(defvar antlr-font-lock-additional-keywords
  `((antlr-invalidate-context-cache)
    ("\\$setType[ \t]*(\\([A-Z\300-\326\330-\337]\\sw*\\))"
     (1 antlr-font-lock-tokendef-face))
    ("}\\(\\?\\)"
     (1 font-lock-reference-face))
    ("\\$\\sw+" (0 font-lock-keyword-face))
    ;; the tokens are already fontified as string/docstrings:
    (,(lambda (limit)
	(antlr-re-search-forward "\"\\(\\sw+\\)\"" limit))
     (1 antlr-font-lock-literal-face t))
    (,(lambda (limit)
	(antlr-re-search-forward
	 "^\\(class\\)[ \t]+\\([A-Z\300-\326\330-\337]\\sw*\\)[ \t]+\\(extends[ \t]+\\(Lexer\\|Parser\\|TreeParser\\)\\)[ \t]*;" limit))
     (1 antlr-font-lock-keyword-face)
     (2 antlr-font-lock-ruledef-face)
     (3 antlr-font-lock-keyword-face))
    (,(lambda (limit)
	(antlr-re-search-forward
	 "\\<\\(header\\|options\\|tokens\\|exception\\|catch\\|returns\\)\\>"
	 limit))
     (1 antlr-font-lock-keyword-face))
    (,(lambda (limit)
	(antlr-re-search-forward
	 "^\\(private\\|public\\|protected\\)\\>\\([ \t]+\\(\\sw+\\)\\)?"
	 limit))
     (1 font-lock-type-face)		; not XEmacs' java level-3 fruit salad
     (3 (if (antlr-upcase-p (char-after (match-beginning 3)))
	    'antlr-font-lock-tokendef-face
	  'antlr-font-lock-ruledef-face) nil t))
    (,(lambda (limit)
	(antlr-re-search-forward "^\\sw+" limit))
     (0 (if (antlr-upcase-p (char-after (match-beginning 0)))
	    'antlr-font-lock-tokendef-face
	  'antlr-font-lock-ruledef-face) nil t))
    (,(lambda (limit)
	(antlr-re-search-forward "\\<\\(\\sw+\\)[ \t]*:" limit))
     (1 antlr-font-lock-default-face))
    (,(lambda (limit)
	(antlr-re-search-forward "\\<\\(\\sw+[ \t]*=[ \t]*\\)?\\(\\sw+[ \t]*:[ \t]*\\)?\\(\\sw+\\)" limit))
     (1 antlr-font-lock-default-face nil t) ; fool java-font-lock-keywords
     (3 (if (antlr-upcase-p (char-after (match-beginning 3)))
	    'antlr-font-lock-tokenref-face
	  'antlr-font-lock-ruleref-face))))
  "Font-lock keywords for ANTLR's normal grammar code.
See `antlr-language-alist' for the keywords of actions.")

(defvar antlr-font-lock-defaults
  '(antlr-font-lock-keywords
    nil nil ((?_ . "w") (?\( . ".") (?\) . ".")) beginning-of-defun)
  "Font-lock defaults used for ANTLR syntax coloring.
The SYNTAX-ALIST element is also used to initialize
`antlr-action-syntax-table'.")


;;;===========================================================================
;;;  Internal variables
;;;===========================================================================

(defvar antlr-mode-hook nil
  "Hook called by `antlr-mode'.")

;; used for "in Java/C++ code" = syntactic-depth>0
(defvar antlr-action-syntax-table nil
  "Syntax table used for ANTLR action parsing.
Initialized by `java-mode-syntax-table', i.e., the syntax table used for
grammar files, changed by SYNTAX-ALIST in `antlr-font-lock-defaults'.
This table should be selected if you use `buffer-syntactic-context' and
`buffer-syntactic-context-depth' in order not to confuse their
context_cache.")

(defvar antlr-mode-abbrev-table nil
  "Abbreviation table used in `antlr-mode' buffers.")
(define-abbrev-table 'antlr-mode-abbrev-table ())



;;;;##########################################################################
;;;;  The Code
;;;;##########################################################################


;;;===========================================================================
;;;  Syntax functions -- Emacs vs XEmacs dependent
;;;===========================================================================

(defun antlr-scan-sexps-internal (from count &optional dummy no-error)
  "Like `scan-sexps' but return nil instead of signalling an error."
  (if no-error
      (condition-case nil
	  (scan-sexps from count)
	(t nil))
    (scan-sexps from count)))

(defun antlr-xemacs-bug-workaround (&rest dummies)
  "Invalidate context_cache for syntactical context information."
  ;; XEmacs bug workaround
  (save-excursion
    (set-buffer (get-buffer-create " ANTLR XEmacs bug workaround"))
    (buffer-syntactic-context-depth))
  nil)

(defun antlr-fast-syntactic-context ()
  "Return some syntactic context information.
Return `string' if point is within a string, `block-comment' or
`comment' is point is within a comment or the depth within all
parenthesis-syntax delimiters at point otherwise.
WARNING: this may alter match-data."
  (or (buffer-syntactic-context) (buffer-syntactic-context-depth)))

(defun antlr-slow-syntactic-context ()
  "Return some syntactic context information.
Return `string' if point is within a string, `block-comment' or
`comment' is point is within a comment or the depth within all
parenthesis-syntax delimiters at point otherwise.
WARNING: this may alter match-data."
  (let ((orig (point)))
    (beginning-of-defun)
    (let ((state (parse-partial-sexp (point) orig)))
      (goto-char orig)
      (cond ((nth 3 state) 'string)
	    ((nth 4 state) 'comment)	; block-comment? -- we don't care
	    (t (car state))))))


;;;===========================================================================
;;;  Misc functions
;;;===========================================================================

(defun antlr-upcase-p (char)
  "Non-nil, if CHAR is an uppercase character (if CHAR was a char)."
  ;; in XEmacs, upcase only works for ASCII
  (or (and (<= ?A char) (<= char ?Z))
      (and (<= ?\300 char) (<= char ?\337)))) ; ?\327 is no letter

(defun antlr-re-search-forward (regexp bound)
  "Search forward from point for regular expression REGEXP.
Set point to the end of the occurrence found, and return point.  Return
nil if no occurence was found.  Do not search within comments, strings
and actions/semantic predicates.  BOUND bounds the search; it is a
buffer position.  See also the functions `match-beginning', `match-end'
and `replace-match'."
  ;; WARNING: Should only be used with `antlr-action-syntax-table'!
  (let ((continue t))
    (while (and (re-search-forward regexp bound 'limit)
		(save-match-data
		  (if (eq (antlr-syntactic-context) 0) (setq continue nil) t))))
    (if continue nil (point))))

(defun antlr-search-forward (string)
  "Search forward from point for STRING.
Set point to the end of the occurrence found, and return point.  Return
nil if no occurence was found.  Do not search within comments, strings
and actions/semantic predicates."
  ;; WARNING: Should only be used with `antlr-action-syntax-table'!
  (let ((continue t))
    (while (and (search-forward string nil 'limit)
		(if (eq (antlr-syntactic-context) 0) (setq continue nil) t)))
    (if continue nil (point))))

(defun antlr-search-backward (string)
  "Search backward from point for STRING.
Set point to the beginning of the occurrence found, and return point.
Return nil if no occurence was found.  Do not search within comments,
strings and actions/semantic predicates."
  ;; WARNING: Should only be used with `antlr-action-syntax-table'!
  (let ((continue t))
    (while (and (search-backward string nil 'limit)
		(if (eq (antlr-syntactic-context) 0) (setq continue nil) t)))
    (if continue nil (point))))

(defsubst antlr-skip-sexps (count)
  "Skip the next COUNT balanced expressions and the comments after it.
Return position before the comments after the last expression."
  (goto-char (or (antlr-scan-sexps (point) count nil t) (point-max)))
  (prog1 (point)
    (c-forward-syntactic-ws)))


;;;===========================================================================
;;;  font-lock
;;;===========================================================================

;; is this currently XEmacs specific?
(defun antlr-font-lock-keywords ()
  "Return font-lock keywords for current buffer.
See `antlr-font-lock-additional-keywords', `antlr-language' and
`antlr-font-lock-maximum-decoration'."
  (if (eq antlr-font-lock-maximum-decoration 'none)
      antlr-font-lock-additional-keywords
    (append antlr-font-lock-additional-keywords
	    (eval (let ((major-mode antlr-language)) ; dynamic
			(font-lock-choose-keywords
			 (caddr (assq antlr-language antlr-language-alist))
			 (if (eq antlr-font-lock-maximum-decoration 'inherit)
			     font-lock-maximum-decoration
			   antlr-font-lock-maximum-decoration)))))))


;;;===========================================================================
;;;  imenu support
;;;===========================================================================

(defun antlr-imenu-create-index-function ()
  "Return imenu index-alist for ANTLR gramar files."
  (let ((items nil)
	(lexer nil)
	(parser nil)
	(treeparser nil)
	(classes nil)
	(semi (point-max)))
    ;; would require imenu for compilation -- nobody is missing these msgs...
    ;;(imenu-progress-message prev-pos 0)
    (with-syntax-table antlr-action-syntax-table
      ;; We stick to the imenu standard and search backwards, although I don't
      ;; think this is right.  It is slower and more likely not to work during
      ;; editing (you are more likely to add functions to the end of the file).
      (while semi
	(goto-char semi)
	(if (setq semi (antlr-search-backward ";"))
	    (progn (forward-char) (antlr-skip-exception-part t))
	  (antlr-skip-grammar-header t))
	(if (looking-at "class[ \t]+\\(\\sw+\\)[ \t]+extends[ \t]+\\(Lexer\\|Parser\\|TreeParser\\)")
	    (progn
	      (push (cons (match-string 1)
			  (if imenu-use-markers
			      (copy-marker (match-beginning 1))
			    (match-beginning 1)))
		    classes)
	      (cond ((eq (char-after (match-beginning 2)) ?P)
		     (setq parser (nconc items parser)))
		    ((eq (char-after (match-beginning 2)) ?L)
		     (setq lexer (nconc items lexer)))
		    (t
		     (setq treeparser (nconc items treeparser))))
	      (setq items nil))
	  (if (looking-at "p\\(ublic\\|rotected\\|rivate\\)")
	      (antlr-skip-sexps 1))
	  (when (looking-at "\\sw+")
	    (push (cons (match-string 0)
			(if imenu-use-markers
			    (copy-marker (match-beginning 0))
			  (match-beginning 0)))
		  items)))))
	;;;(imenu-progress-message prev-pos nil t)))
    (if items				; outside any class
	 (if parser
	     (push (cons "Miscellaneous" items) parser)
	   (setq parser items)))
    (if treeparser (push (cons "TreeParser" treeparser) parser))
    (if lexer (push (cons "Lexer" lexer) parser))
    (if classes (cons (cons "Classes" classes) parser) parser)))


;;;===========================================================================
;;;  Parse grammar files (internal functions)
;;;===========================================================================

(defun antlr-skip-exception-part (skip-comment)
  "Skip exception part of current rule, i.e., everything after `;'.
If SKIP-COMMENT is non-nil, also skip the comment after that part."
  (let ((pos (point)))
    (c-forward-syntactic-ws)
    (while (looking-at "exception\\>")
      (setq pos (antlr-skip-sexps 1))
      (if (looking-at "\\[") (setq pos (antlr-skip-sexps 1)))
      (while (looking-at "catch\\>") (setq pos (antlr-skip-sexps 3))))
    (while (looking-at "options\\>\\|tokens\\>")
      (setq pos (antlr-skip-sexps 2)))
    (if (looking-at "{") (setq pos (antlr-skip-sexps 1)))
    (or skip-comment (goto-char pos))))

(defun antlr-skip-grammar-header (skip-comment)
  "Skip the grammar header and file options.
If SKIP-COMMENT is non-nil, also skip the comment after that part."
  (let* ((pos (point))
	 (pos0 pos))
    (c-forward-syntactic-ws)
    (if skip-comment (setq pos0 (point)))
    (if (looking-at "header\\>") (setq pos (antlr-skip-sexps 2)))
    (if (looking-at "options\\>") (setq pos (antlr-skip-sexps 2)))
    (if (looking-at "{") (setq pos (antlr-skip-sexps 1)))
    (or skip-comment (goto-char pos))
    pos0))

(defun antlr-next-rule (arg skip-comment)
  "Move forward to next end of rule.  Do it ARG many times.
Negative argument ARG means move back to ARGth preceding end of rule.
The behaviour is not defined when ARG is zero.  If SKIP-COMMENT is
non-nil, move to beginning of the rule."
  ;; WARNING: Should only be used with `antlr-action-syntax-table'!
  ;; PRE: ARG<>0
  (let ((pos (point))
	(beg (point)))
    ;; first look whether point is in exception part
    (if (antlr-search-backward ";")
	(progn
	  (setq beg (point))
	  (forward-char)
	  (antlr-skip-exception-part skip-comment))
      (antlr-skip-grammar-header skip-comment))
    (if (< arg 0)
	(unless (and (< (point) pos) (zerop (incf arg)))
	  ;; if we have moved backward, we already moved one defun backward
	  (goto-char beg)		; rewind (to ";" / point)
	  (while (and arg (<= (incf arg) 0))
	    (if (antlr-search-backward ";")
		(setq beg (point))
	      (when (>= arg -1)
		;; try grammar header
		(setq pos (antlr-skip-grammar-header skip-comment))
		(if (zerop arg)
		    (if (>= (point) beg)
			(goto-char (if (>= pos beg) (point-min) pos)))
		  (goto-char (if (or (>= (point) beg) (= (point) pos))
				 (point-min) pos))))
	      (setq arg nil)))
	  (when arg			; always found a ";"
	    (forward-char)
	    (antlr-skip-exception-part skip-comment)))
      (if (<= (point) pos)		; moved backward?
	  (goto-char pos)		; rewind
	(decf arg))			; already moved one defun forward
      (unless (zerop arg)
	(while (>= (decf arg) 0)
	  (antlr-search-forward ";"))
	(antlr-skip-exception-part skip-comment)))))

(defun antlr-outside-rule-p ()
  "Non-nil if point is outside a grammar rule.
Move to the beginning of the current rule if point is inside a grammar."
  ;; WARNING: Should only be used with `antlr-action-syntax-table'!
  (let ((pos (point)))
    (antlr-next-rule -1 nil)
    (let ((between (or (bobp) (< (point) pos))))
      (c-forward-syntactic-ws)
      (and between (> (point) pos) (goto-char pos)))))


;;;===========================================================================
;;;  Parse grammar files (commands)
;;;===========================================================================

(defun antlr-inside-rule-p ()
  "Non-nil if point is inside a grammar rule."
  (save-excursion
    (with-syntax-table antlr-action-syntax-table
      (not (antlr-outside-rule-p)))))

(defun antlr-end-of-rule (&optional arg)
  "Move forward to next end of rule.  Do it ARG [default: 1] many times.
Negative argument ARG means move back to ARGth preceding end of rule.
If ARG is zero, run `antlr-end-of-body'."
  (interactive "p")
  (if (zerop arg)
      (antlr-end-of-body)
    (with-syntax-table antlr-action-syntax-table
      (antlr-next-rule arg nil))))

(defun antlr-beginning-of-rule (&optional arg)
  "Move backward to preceding beginning of rule.  Do it ARG many times.
Negative argument ARG means move forward to ARGth next beginning of
rule.  If ARG is zero, run `antlr-beginning-of-body'."
  (interactive "p")
  (if (zerop arg)
      (antlr-beginning-of-body)
    (with-syntax-table antlr-action-syntax-table
      (antlr-next-rule (- arg) t))))

(defun antlr-end-of-body (&optional msg)
  "Move to position after the `;' of the current rule.
With optional prefix arg MSG, move to `:'."
  (interactive)
  (with-syntax-table antlr-action-syntax-table
    (let ((orig (point)))
      (if (antlr-outside-rule-p)
	  (error "Outside an ANTLR rule")
	(let ((bor (point)))
	  (if (< (antlr-skip-grammar-header t) (point))
	      (progn (goto-char orig)
		     (error (or msg "No `;' in the grammar header")))
	    (antlr-search-forward ";")
	    (when msg
	      (if (< (point)
		     (progn (goto-char bor)
			    (or (antlr-search-forward ":") (point-max))))
		  (progn (goto-char orig)
			 (error msg))
		(c-forward-syntactic-ws)))))))))

(defun antlr-beginning-of-body ()
  "Move to the first element after the `:' of the current rule."
  (interactive)
  (antlr-end-of-body "No `:' in the grammar header"))


;;;===========================================================================
;;;  Indentation
;;;===========================================================================

(defun antlr-indent-line ()
  "Indent the current line as ANTLR grammar code.
The indentation of non-comment lines are calculated by `c-basic-offset',
multiplied by:
 - the level of the paren/brace/bracket depth,
 - plus 0/2/1, depending on the position inside the rule: header, body,
   exception part,
 - minus 1 if `antlr-indent-item-regexp' matches the beginning of the
   line starting from the first non-blank.

Lines inside block commments are not changed or indented by
`c-indent-line', see `antlr-indent-comment'."
  (let ((orig (point)) bol boi indent syntax)
    (beginning-of-line)
    (setq bol (point))
    (skip-chars-forward " \t")
    (setq boi (point))
    ;; check syntax at beginning of indentation ------------------------------
    (with-syntax-table antlr-action-syntax-table
      (antlr-invalidate-context-cache)
      (cond ((symbolp (setq syntax (antlr-syntactic-context)))
	     (setq indent nil))		; block-comments, strings, (comments)
	    ((progn
	       (antlr-next-rule -1 t)
	       (if (antlr-search-forward ":") (< boi (1- (point))) t))
	     (setq indent 0))		; in rule header
	    ((if (antlr-search-forward ";") (< boi (point)) t)
	     (setq indent 2))		; in rule body
	    (t
	     (forward-char)
	     (antlr-skip-exception-part nil)
	     (setq indent (if (> (point) boi) 1 0))))) ; in exception part?
    ;; compute the corresponding indentation and indent ----------------------
    (if (null indent)
	(progn
	  (goto-char orig)
	  (and (eq antlr-indent-comment t)
	       (not (eq syntax 'string))
	       (c-indent-line)))
      ;; do it ourselves
      (goto-char boi)
      (antlr-invalidate-context-cache)
      (incf indent (antlr-syntactic-context))
      (and (> indent 0) (looking-at antlr-indent-item-regexp) (decf indent))
      (setq indent (* indent c-basic-offset))
      ;; the usual major-mode indent stuff
      (setq orig (- (point-max) orig))
      (unless (= (current-column) indent)
	(delete-region bol boi)
	(beginning-of-line)
	(indent-to indent))
      ;; If initial point was within line's indentation,
      ;; position after the indentation.  Else stay at same point in text.
      (if (> (- (point-max) orig) (point))
	  (goto-char (- (point-max) orig))))))

(defun antlr-indent-command (&optional arg)
  "Indent the current line or insert tabs/spaces.
With optional prefix argument ARG or if the previous command was this
command, insert ARG tabs or spaces according to `indent-tabs-mode'.
Otherwise, indent the current line with `antlr-indent-line'."
  (interactive "P")
  (if (or arg (eq last-command 'antlr-indent-command))
      (insert-tab arg)
    (let ((antlr-indent-comment (and antlr-indent-comment t))) ; dynamic
      (antlr-indent-line))))


;;;===========================================================================
;;;  Mode entry
;;;===========================================================================

(defun antlr-c-common-init ()
  ;; `c-common-init' except menu, auto-hungry and c-style stuff
  ;; X/Emacs 20 only
  (make-local-variable 'paragraph-start)
  (make-local-variable 'paragraph-separate)
  (make-local-variable 'paragraph-ignore-fill-prefix)
  (make-local-variable 'require-final-newline)
  (make-local-variable 'parse-sexp-ignore-comments)
  (make-local-variable 'indent-line-function)
  (make-local-variable 'indent-region-function)
  (make-local-variable 'comment-start)
  (make-local-variable 'comment-end)
  (make-local-variable 'comment-column)
  (make-local-variable 'comment-start-skip)
  (make-local-variable 'comment-multi-line)
  (make-local-variable 'outline-regexp)
  (make-local-variable 'outline-level)
  (make-local-variable 'adaptive-fill-regexp)
  (make-local-variable 'adaptive-fill-mode)
  (make-local-variable 'imenu-generic-expression) ;set in the mode functions
  (and (boundp 'comment-line-break-function)
       (make-local-variable 'comment-line-break-function))
  ;; Emacs 19.30 and beyond only, AFAIK
  (if (boundp 'fill-paragraph-function)
      (progn
	(make-local-variable 'fill-paragraph-function)
	(setq fill-paragraph-function 'c-fill-paragraph)))
  ;; now set their values
  (setq paragraph-start (concat page-delimiter "\\|$")
	paragraph-separate paragraph-start
	paragraph-ignore-fill-prefix t
	require-final-newline t
	parse-sexp-ignore-comments t
	indent-line-function 'c-indent-line
	indent-region-function 'c-indent-region
	outline-regexp "[^#\n\^M]"
	outline-level 'c-outline-level
	comment-column 32
	comment-start-skip "/\\*+ *\\|// *"
	comment-multi-line nil
	comment-line-break-function 'c-comment-line-break-function
	adaptive-fill-regexp nil
	adaptive-fill-mode nil)
  ;; we have to do something special for c-offsets-alist so that the
  ;; buffer local value has its own alist structure.
  (setq c-offsets-alist (copy-alist c-offsets-alist))
  ;; setup the comment indent variable in a Emacs version portable way
  ;; ignore any byte compiler warnings you might get here
  (make-local-variable 'comment-indent-function)
  (setq comment-indent-function 'c-comment-indent))

;;;###autoload
(defun antlr-mode ()
  "Major mode for editing ANTLR grammar files.
\\{antlr-mode-map}"
  (interactive)
  (c-initialize-cc-mode)		; for java syntax table
  (kill-all-local-variables)
  ;; ANTLR specific ----------------------------------------------------------
  (setq major-mode 'antlr-mode
	mode-name "Antlr")
  (setq local-abbrev-table antlr-mode-abbrev-table)
  (set-syntax-table java-mode-syntax-table)
  (unless antlr-action-syntax-table
    (let ((slist (nth 3 antlr-font-lock-defaults)))
      (setq antlr-action-syntax-table
	    (copy-syntax-table java-mode-syntax-table))
      (while slist
	(modify-syntax-entry (caar slist) (cdar slist)
			     antlr-action-syntax-table)
	(setq slist (cdr slist)))))
  (use-local-map antlr-mode-map)
  (make-local-variable 'antlr-language)
  (unless antlr-language
    (save-excursion
      (goto-char (point-min))
      (setq antlr-language
	    (car (or (and (re-search-forward (cdr antlr-language-limit-n-regexp)
					(car antlr-language-limit-n-regexp)
					t)
			  (find (match-string 1) antlr-language-alist
				:key 'cdadr :test 'member))
		     (find nil antlr-language-alist
			   :key 'cdadr :test 'member))))))
  (if (stringp (caadr (assq antlr-language antlr-language-alist)))
      (setq mode-name
	    (concat "Antlr/"
		    (caadr (assq antlr-language antlr-language-alist)))))
  ;; indentation, for the C engine -------------------------------------------
  (antlr-c-common-init)
  (setq indent-line-function 'antlr-indent-line
	indent-region-function nil)	; too lazy
  (setq comment-start "// "
 	comment-end "")
  (c-set-style "java")
  (if (eq antlr-language 'c++-mode)
      (setq c-conditional-key c-C++-conditional-key
	    c-comment-start-regexp c-C++-comment-start-regexp
	    c-class-key c-C++-class-key
	    c-extra-toplevel-key c-C++-extra-toplevel-key
	    c-access-key c-C++-access-key
	    c-recognize-knr-p nil)
    (setq c-conditional-key c-Java-conditional-key
	  c-comment-start-regexp c-Java-comment-start-regexp
	  c-class-key c-Java-class-key
	  c-method-key nil
	  c-baseclass-key nil
	  c-recognize-knr-p nil
	  c-access-key c-Java-access-key)
    (and (boundp 'c-inexpr-class-key) (boundp 'c-Java-inexpr-class-key)
	 (setq c-inexpr-class-key c-Java-inexpr-class-key)))
  ;; various -----------------------------------------------------------------
  (make-local-variable 'font-lock-defaults)
  (setq font-lock-defaults antlr-font-lock-defaults)
  (easy-menu-add antlr-mode-menu)
  (make-local-variable 'imenu-create-index-function)
  (setq imenu-create-index-function 'antlr-imenu-create-index-function)
  (make-local-variable 'imenu-generic-expression)
  (setq imenu-generic-expression t)	; fool stupid test
  (and antlr-imenu-name			; there should be a global variable...
       (fboundp 'imenu-add-to-menubar)
       (imenu-add-to-menubar
	(if (stringp antlr-imenu-name) antlr-imenu-name "Rules")))
  (antlr-set-tabs)
  (run-hooks 'antlr-mode-hook))

;;;###autoload
(defun antlr-set-tabs ()
  "Use ANTLR's convention for TABs according to `antlr-tab-offset-alist'.
Used in `antlr-mode'.  Also a useful function in `java-mode-hook'."
  (if buffer-file-name
      (let ((alist antlr-tab-offset-alist) elem)
	(while alist
	  (setq elem (pop alist))
	  (and (or (null (car elem)) (eq (car elem) major-mode))
	       (or (null (cadr elem))
		   (string-match (cadr elem) buffer-file-name))
	       (setq tab-width 4
		     indent-tabs-mode t))))))

;;; antlr-mode.el ends here
