options {
    language = "Sather";
}
{
  class MAIN is
    main( args : ARRAY{STR} ) is
       AST_TEST{ANTLR_COMMON_TOKEN,ANTLR_COMMON_AST}::test;
    end;
  end;
}
class AST_TEST extends Parser;
options {
	buildAST = true;
}

/*  Test the equals, equals_subtree, and find_all methods plus AST enumeration.
    The output should match the contents of file test.out. 
 */
{
        println( s : STR ) is
          #OUT + s + "\n";
        end;

	test is
		r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17 : BOOL;

		t : AST := @([ASSIGN,"="], [ID,"a"], [INT,"1"]); -- build "a=1" tree
		println("t is " + t.str_list);
		u : AST := @([ASSIGN,"="], [ID,"b"]); -- build "b=?" tree
		println("u is " + u.str_list);
		v : AST := @([ASSIGN,"="], [INT,"4"]); -- build "4=?" tree
		println("v is " + v.str_list);
		w : AST := @[ASSIGN,"="]; -- build "=" tree
		println("w is " + w.str_list);
		println("");

	        r1 := t.equals_tree(t);	
                r2 := t.equals_tree(u);
                r3 := t.equals_tree(v);
                r4 := t.equals_tree(w);
                r5 := t.equals_tree(void);

		println("t.equals_tree(t) is " + r1 );
		println("t.equals_tree(u) is " + r2 );
		println("t.equals_tree(v) is " + r3 );
		println("t.equals_tree(w) is " + r4 );
		println("t.equals_tree(void) is " + r5 );

		println("");

                r6 := t.equals_tree_partial(t);	
                r7 := t.equals_tree_partial(u);
                r8 := t.equals_tree_partial(v);
                r9 := t.equals_tree_partial(w);
                r10 := t.equals_tree_partial(void);

		println("t.equals_tree_partial(t) is " + r6 ); 
		println("t.equals_tree_partial(u) is " + r7 ); 
		println("t.equals_tree_partial(v) is " + r8 ); 
		println("t.equals_tree_partial(w) is " + r9 ); 
		println("t.equals_tree_partial(void) is " + r10 );

		println("");

		-- (A (B C (A B)) (A B) (F (A B)) (A (A B)) ) J
		-- Visually:
                -- A---------------------J
                -- |
                -- B-----A-----F----A
                -- |     |     |    |
                -- C--A  B     A    A
                --    |        |    |
                --    B        B    B
		--

		a : AST := @(void,
					([A,"A"],
						([B,"B"], [C,"C"], ([A,"A"],[B,"B"])),
						([A,"A"],[B,"B"]),
						([F,"F"], @([A,"A"], [B,"B"])),
						([A,"A"], @([A,"A"], [B,"B"]))),
					[J,"J"]); 
		println("a is "+a.str_list+"\n");
		println("              A---------------------J");
		println("              |");
		println("              B-----A-----F----A");
		println("              |     |     |    |");
		println("              C--A  B     A    A");
		println("                 |        |    |");
		println("                 B        B    B\n");

		x : AST := a.first_child.next_sibling;
		println("x is second sibling of upperleftmost A: " + x.str_list);
		y : AST := a.first_child.next_sibling.first_child;
		println("y is child B of x: " + y.str_list);

                r11 := x.equals_tree(@([A,"A"],[B,"B"]));
                r12 := x.equals_list(@([A,"A"],[B,"B"]));
                r13 := x.equals_list_partial(@([A,"A"],[B,"B"]));
                r14 := a.equals_tree(@([A,"A"],[B,"B"]));
                r15 := a.equals_tree_partial(@([A,"A"],[B,"B"]));
                r16 := y.equals_list(@[B,"B"]);
                r17 := y.equals_list(@[B,"B"]);

		println("x.equals_tree(@(A B)) is " + r11 ); 
		println("x.equals_list(@(A B)) is " + r12 ); 
		println("x.equals_list_partial(@(A B)) is " + r13 ); 
		println("a.equals_tree(@(A B)) is " + r14 ); 
		println("a.equals_tree_partial(@(A B)) is " + r15 ); 
		println("y.equals_list(@[B]) is " + r16 ); 
		println("y.equals_list_partial(@[B]) is " + r17 ); 

		enum : ARRAY{AST};
		println("\na.find_all_partial(@(A B)):");
		enum := a.find_all_partial(@([A,"A"],[B,"B"]));
	        loop 
	           println( enum.elt!.str_list );
                end;

		println("\na.find_all_partial(@[A])):");
		enum := a.find_all_partial(@[A,"A"]);
	        loop 
	           println( enum.elt!.str_list );
                end;

		println("\na.find_all(@(A B)):");
		enum := a.find_all(@([A,"A"],[B,"B"]));
	        loop 
	           println( enum.elt!.str_list );
                end;

		-- check results
		println("\nTest results:");
		if ( r1=true and r2=false and r3=false and r4=false and
			 r5=false and r11=true and r14=false) then
			println("equals_tree is ok");
		else 
			println("equals_tree is bad");
		end;

		if ( r6=true and r7=false and r8=false and r9=true and r10=true ) then
			println("equals_tree_partial is ok");
		else 
			println("equals_tree_partial is bad");
                end;
		if ( r12=false and r16=true ) then
			println("equals_list is ok");
		else 
			println("equals_list is bad");
 		end;
		if ( r13=true and r17=true ) then
			println("equals_list_partial is ok");
		else 
			println("equals_list_partial is bad");
		end;
	end;
}


defTokenTypes
	:	ID INT ASSIGN PLUS A B C D E F G H I J K
	;
