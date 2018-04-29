module FamilyTreeHomework where

data Gender = Male | Female deriving (Show, Eq)
data Person = Person Gender String deriving (Show, Eq)
data FamilyTree = Empty | Family Person Person [FamilyTree] | Individual Person deriving (Show, Eq)

addchild        :: FamilyTree   -> Person -> FamilyTree
ischild         :: FamilyTree   -> Person -> Bool

childrenOf      :: FamilyTree   -> Person  -> [Person]
marryTo         :: FamilyTree   -> Person  -> Person -> FamilyTree

mother          :: FamilyTree   -> Person -> Maybe Person
brothers        :: FamilyTree   -> Person -> [Person]

-- DO NOT MODIFY ABOVE THIS LINE
-- Start Here

-------Yardimcilar------

y2ischild :: FamilyTree -> Person -> Bool
yischild :: [FamilyTree] -> Person -> Bool
y2childrenOf :: [FamilyTree] -> Person -> [Person]
ychildrenOf :: [FamilyTree] -> [Person]
samesex :: Person -> Person -> Bool
ymarryTo :: [FamilyTree] -> Person -> Person -> [FamilyTree]
isfemale :: Person -> Bool
ymother :: [FamilyTree] -> Person -> Maybe Person
ybrothers :: [FamilyTree] -> Person -> [Person]
ayikla :: [Person] -> Person -> [Person]
yfperson :: [FamilyTree] -> Person -> FamilyTree
fperson :: FamilyTree -> Person -> FamilyTree
ayikla2 :: [Person] -> FamilyTree -> Person -> [Person]
ayikla3 :: [Person] -> [Person]
-------
addchild (Family x y z) t=(Family x y ((Individual t):z))
addchild x t = x
-------
y2ischild a b = case a of (Family c d _) -> (b==c) || (b==d)
                          (Individual e) -> e==b
yischild [] a =False
yischild (x:[]) a = case x of (Family b c d) -> (a==b) || (a==c)
                              (Individual e) -> e==a
yischild (x:xs) a= (y2ischild x a) || (yischild xs a) 


ischild Empty _ =False
ischild (Individual a) _=False
ischild (Family _ _ a) b=case a of []                -> False
                                   (Family c d _):[] -> (c==b) || (d==b)
                                   (Individual e):[] -> e==b
                                   all@(x:xs)        -> yischild all b
-------
y2childrenOf [] _ =[]
y2childrenOf [Individual _] _=[]
y2childrenOf [Family a b c] d=if a==d || b==d then (ychildrenOf c) else (childrenOf(Family a b c) d)

y2childrenOf ((Family a b c):xs) d=if a==d || b==d then (ychildrenOf c) else (childrenOf(Family a b c) d)++(y2childrenOf xs d)
y2childrenOf((Individual a):xs) d=if a==d then [] else (y2childrenOf xs d)

ychildrenOf []=[]
ychildrenOf (x:xs)=case x of (Family a b _) -> a:b:(ychildrenOf xs)
                             (Individual c) -> c:(ychildrenOf xs)
						   
childrenOf Empty _=[]
childrenOf (Family a b c) d=if a==d || b==d then ychildrenOf c else (y2childrenOf c d)
childrenOf _ _=[]
--------

samesex (Person a _) (Person b _)=if a==b then True else False

ymarryTo [] _ _=[]
ymarryTo [Individual a] b c=if a/=b then [Individual a] else (if (samesex a c) then [Individual a] else [Family a c []])
ymarryTo [Family a b e] c d
              |a==c =if (samesex a d) then [Family a b e] else [Family a d e]
			  |b==c =if (samesex b d) then [Family a b e] else [Family d b e]
			  |otherwise=[Family a b (ymarryTo e c d)]
ymarryTo ((Individual a):xs) b c=if a/=b then ((Individual a):(ymarryTo xs b c)) else(if (samesex a c) then (Individual a):xs else ((Family a c []):xs))
ymarryTo ((Family a b e):xs) c d
              |a==c =if (samesex a d) then (Family a b e):xs else (Family a d e):xs
			  |b==c =if (samesex b d) then (Family a b e):xs else (Family d b e):xs
			  |otherwise=(Family a b (ymarryTo e c d)):(ymarryTo xs c d)

marryTo Empty _ _=Empty
marryTo (Individual a) b c=if a/=b then (Individual a) else (if (samesex a c) then (Individual a) else (Family a c []))
marryTo (Family a b e) c d
              |a==c =if (samesex a d) then (Family a b e) else (Family a d e)
			  |b==c =if (samesex b d) then (Family a b e) else (Family d b e)
			  |otherwise=(Family a b (ymarryTo e c d))
-------
isfemale (Person a _)=if a==Female then True else False

ymother [] _=Nothing
ymother [Individual _] _=Nothing
ymother [Family a b c] d=(mother (Family a b c) d)
ymother ((Individual _):xs) d=(ymother xs d)
ymother ((Family a b c):xs) d=if (mother (Family a b c) d)==Nothing then (ymother xs d) else (mother (Family a b c) d)


mother Empty _=Nothing
mother (Individual _) _=Nothing
mother (Family a b c) d=if (ischild (Family a b c) d) then (if isfemale a then Just a else Just b) else (ymother c d)
-------

ayikla a b=[c|c<-a,c/=b]
ayikla2 a b c=case b of Family d e f->if c==e then ayikla a d else ayikla a e
                        Individual g->ayikla a g
ayikla3 a=[(Person b c)|(Person b c)<-a,if b==Male then True else False]

yfperson [] _=Empty
yfperson [Individual a] b=if a==b then Individual a else Empty
yfperson [Family a b c] d
              |(a==d || b==d) =Family a b c
			  |otherwise=fperson (Family a b c) d
yfperson ((Individual a):xs) b=if a==b then Individual a else yfperson xs b
yfperson ((Family a b c):xs) d
              |(a==d || b==d) =Family a b c
			  |(fperson (Family a b c) d==Empty) =yfperson xs d
			  |otherwise=fperson (Family a b c) d 

fperson Empty _=Empty
fperson (Individual a) b=if a==b then Individual a else Empty 
fperson (Family a b c) d
              |(a==d || b==d) =Family a b c
			  |otherwise=yfperson c d

ybrothers [] _=[]
ybrothers [Individual _] _=[]
ybrothers [Family a b c] d
               |(a/=d && b/=d)=if (ischild (Family a b c) d) then ayikla3 (ayikla2 (ayikla (childrenOf (Family a b c) a) d) (fperson (Family a b c) d) d) else ybrothers c d
               |otherwise=[]
ybrothers ((Individual _):xs) a=ybrothers xs a
ybrothers ((Family a b c):xs) d=(brothers (Family a b c) d)++(ybrothers xs d)

brothers Empty _=[]
brothers (Individual _) _=[]
brothers (Family a b c) d
               |(a/=d && b/=d)=if (ischild (Family a b c) d) then ayikla3 (ayikla2 (ayikla (childrenOf (Family a b c) a) d) (fperson (Family a b c) d) d) else ybrothers c d
