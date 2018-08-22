:- module(hw5,[configuration/3]).
:- [hardware].

numberOfAdjacentsHelper(_,[],0).
numberOfAdjacentsHelper(SEC,[H|T],NUM) :-
    (adjacent(SEC,H); adjacent(H,SEC)),
    numberOfAdjacentsHelper(SEC,T,N),
    NUM is N+1.
numberOfAdjacentsHelper(SEC,[_|T],NUM) :- numberOfAdjacentsHelper(SEC,T,NUM).

numberOfAdjacents(SEC,NUM) :- sections(S), numberOfAdjacentsHelper(SEC,S,NUM), !.


numberOfOuterEdge(SEC,NUM) :- numberOfAdjacents(SEC,N), NUM is 4-N.

hasOuterEdge(SEC) :- numberOfOuterEdge(SEC,NUM), NUM>0, NUM<4.
isClose(X,Y) :- adjacent(X,Y); adjacent(Y,X).

configurationHelper([],_,PL,PL).
configurationHelper([H|T],CONSTRAINT_LIST,ACC,PL) :-
    sections(S),member(PLACE,S),
    not(member(put(_,PLACE),ACC)),
    (
            ( member(outer_edge(H),CONSTRAINT_LIST), hasOuterEdge(PLACE), append(ACC,[put(H,PLACE)],RES), configurationHelper(T,CONSTRAINT_LIST,RES,PL) ) ;

            ( not(member(outer_edge(H),CONSTRAINT_LIST)), member(close_to(H,COMP1),CONSTRAINT_LIST),
                (
                    ( member(put(COMP1,COMP1_PLACE),ACC),isClose(PLACE,COMP1_PLACE), append(ACC,[put(H,PLACE)],RES), configurationHelper(T,CONSTRAINT_LIST,RES,PL) );
                    ( not(member(put(COMP1,_),ACC)), append(ACC,[put(H,PLACE)],RES), configurationHelper(T,CONSTRAINT_LIST,RES,PL) )
                )
            );

            ( not(member(outer_edge(H),CONSTRAINT_LIST)), member(close_to(COMP2,H),CONSTRAINT_LIST),
                (
                    ( member(put(COMP2,COMP2_PLACE),ACC), isClose(PLACE,COMP2_PLACE), append(ACC,[put(H,PLACE)],RES), configurationHelper(T,CONSTRAINT_LIST,RES,PL) );
                    ( not(member(put(COMP2,_),ACC)), append(ACC,[put(H,PLACE)],RES), configurationHelper(T,CONSTRAINT_LIST,RES,PL) )
                )
            );

            ( not(member(outer_edge(H),CONSTRAINT_LIST)), not(member(close_to(H,_),CONSTRAINT_LIST)), not(member(close_to(_,H),CONSTRAINT_LIST)),
              append(ACC,[put(H,PLACE)],RES), configurationHelper(T,CONSTRAINT_LIST,RES,PL)
            )
    ).

configuration([],[],[]) :- !.
configuration(COMPONENT_LIST,CONSTRAINT_LIST,PLACEMENT_LIST) :-
    length(COMPONENT_LIST,SIZE),
    sections(SEC), length(SEC,SIZE_OF_SEC),
    SIZE =< SIZE_OF_SEC,
    configurationHelper(COMPONENT_LIST,CONSTRAINT_LIST,[],PLACEMENT_LIST).

