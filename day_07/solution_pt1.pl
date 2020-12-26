:- compile(facts).

is_contained(TupX, BagY) :-
	contains(BagY, Contents),
	member(TupX, Contents).

is_contained(TupX, BagY) :-
	contains(BagY, Contents),
	member((_, BagZ), Contents),
	TupX = (_, BagX), BagZ \= BagX,
	is_contained(TupX, BagZ).

n_contained(Bag, N) :-
	findall(X, is_contained((_, Bag), X), Bags),
	sort(Bags, UniqueBags),
	length(UniqueBags, N).
