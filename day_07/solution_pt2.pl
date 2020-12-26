:- compile(facts).

count([], Acc, Acc).
count([(K, Bag) | Rest], Acc, N) :-
	contains_n(Bag, N1),
	NewAcc is Acc + K * (N1 + 1),
	count(Rest, NewAcc, N).

contains_n(Bag, N) :- contains(Bag, Contents), count(Contents, 0, N).
