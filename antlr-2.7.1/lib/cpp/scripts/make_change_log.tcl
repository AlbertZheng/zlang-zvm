#!/bin/sh
# the next line restarts using tclsh \
exec tclsh $0 $*

catch {set file [open "|p4 changes -l ./... ../../antlr/CppCodeGenerator.java ../../antlr/actions/cpp/..." r]}

set cnt 0
set changes {}
set text ""
set change_nr -1
while {![eof $file]} {
	set line [gets $file]

	if { [regexp -- {^Change ([0-9]+).*$} $line dummy tmp] } {
		# append the number to the list of found changes
		lappend changes $tmp

		if { $change_nr != -1 } {
			# were already working on change..
			# so we have text to store..
			set description($change_nr) "$text"
		}

		# remember number...
		set change_nr $tmp
		# reinit text
		set text "[string trim $line]\n"
	} else {
		append text "   [string trim $line]\n"
	}
}

catch {close $file}

set sorted_changes [lsort -integer -decreasing $changes]

foreach change $sorted_changes {
	puts $description($change)
}
