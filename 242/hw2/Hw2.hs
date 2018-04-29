module Hw2 where

data HuffmanTree = Empty | Intermediate Integer HuffmanTree HuffmanTree | Leaf Char Integer deriving (Show,Eq)


frequencies :: [Char] -> [HuffmanTree]

buildTree :: [HuffmanTree] -> HuffmanTree

encode :: HuffmanTree -> [Char] -> [Char]

decode :: HuffmanTree -> [Char] -> [Char]

--DO NOT MODIFY ABOVE THIS LINE
--Start here

----Yardimcilar----
quicksort :: [HuffmanTree] -> [HuffmanTree]
yf :: [Char] -> [HuffmanTree]
group                   :: [HuffmanTree] -> [[HuffmanTree]]
groupBy                 :: (Integer -> Integer -> Bool) -> [HuffmanTree] -> [[HuffmanTree]]
spana                    :: (Integer -> Bool) -> [HuffmanTree] -> ([HuffmanTree],[HuffmanTree])
icsort :: [[HuffmanTree]] -> [[HuffmanTree]]
sort :: [HuffmanTree] -> [HuffmanTree]
mydecode :: HuffmanTree -> [Char] -> BreadCrumbs -> [Char]
goup :: HuffmanTree -> BreadCrumbs -> HuffmanTree
---
sorted liste eleman=[a|a<-liste,a/=eleman]
count liste eleman=sum[1|x<-liste,x==eleman]

quicksort []=[]
quicksort ((Leaf x c):xs)=smallerSorted ++ [Leaf x c] ++ biggerSorted
	where smallerSorted = quicksort [(Leaf a b)|(Leaf a b)<-xs,b<=c]
	      biggerSorted = quicksort [(Leaf a b)|(Leaf a b)<-xs,b>c]
group                   =  groupBy (==)
groupBy _  []           =  []
groupBy eq ((Leaf a x):xs)       =  ((Leaf a x):ys) : groupBy eq zs
                           where (ys,zs) = spana (eq x) xs
spana _ xs@[]            =  (xs, xs)
spana p xs@((Leaf b a):xs')
         | p a          =  let (ys,zs) = spana p xs' in ((Leaf b a):ys,zs)
         | otherwise    =  ([],xs)
quicksort2 []=[]
quicksort2 ((Leaf x c):xs)=smallerSorted ++ [Leaf x c] ++ biggerSorted
	where smallerSorted = quicksort2 [(Leaf a b)|(Leaf a b)<-xs,a<=x]
	      biggerSorted = quicksort2 [(Leaf a b)|(Leaf a b)<-xs,a>x]


yf []=[]
yf [x]=[Leaf x 1]
yf l@(x:xs)=(Leaf x (count l x)):(yf (sorted xs x))

icsort []=[]
icsort (x:xs)=(quicksort2 x):(icsort xs)

func liste []=liste
func liste (x:xs)=func (liste++[x]) xs

frequencies liste=foldl func [] ((icsort(group(quicksort(yf liste)))))

----

kucuk a b= case (a,b) of(Leaf _ num1,Intermediate num2 _ _)          ->(if num2<num1 then True else False)
                        (Intermediate num1 _ _,Leaf _ num2)          ->(if num2<num1 then True else False)
                        (Leaf _ num1,Leaf _ num2)                    ->(if num2<num1 then True else False)
                        (Intermediate num1 _ _,Intermediate num2 _ _)->(if num2<num1 then True else False)

buyukesit a b= case (a,b) of(Leaf _ num1,Intermediate num2 _ _)            ->(if num2>=num1 then True else False)
                            (Intermediate num1 _ _,Leaf _ num2)            ->(if num2>=num1 then True else False)
                            (Leaf _ num1,Leaf _ num2)                      ->(if num2>=num1 then True else False)
                            (Intermediate num1 _ _,Intermediate num2 _ _)  ->(if num2>=num1 then True else False)

sort []     = []
sort (p:xs) = (sort lesser) ++ [p] ++ (sort greater)
    where
        lesser  = filter (kucuk p) xs
        greater = filter (buyukesit p) xs

buildTree [Leaf a b]=Leaf a b
buildTree [Intermediate a b c]=Intermediate a b c
buildTree ((Leaf a b):(Leaf c d):xs)
           |b<=d =buildTree(sort((Intermediate (b+d) (Leaf a b) (Leaf c d)):xs))
		   |b>d =buildTree(sort((Intermediate (b+d) (Leaf c d) (Leaf a b)):xs))
buildTree ((Leaf a b):(Intermediate c d e):xs)
           |b<=c =buildTree(sort((Intermediate (b+c) (Leaf a b) (Intermediate c d e)):xs))
		   |b>c =buildTree(sort((Intermediate (b+c) (Intermediate c d e) (Leaf a b)):xs))
buildTree ((Intermediate a b c):(Leaf d e):xs)
           |a<e =buildTree(sort((Intermediate (a+e) (Intermediate a b c) (Leaf d e)):xs))
		   |a>=e =buildTree(sort((Intermediate (a+e) (Leaf d e) (Intermediate a b c)):xs))
buildTree ((Intermediate a b c):(Intermediate d e f):xs)
           |a<=d =buildTree(sort((Intermediate (a+d) (Intermediate a b c) (Intermediate d e f)):xs))
		   |a>d =buildTree(sort((Intermediate (a+d) (Intermediate d e f) (Intermediate a b c)):xs))
----

encode _ []=[]
encode a (x:xs)=(myencode a x)++(encode a xs) 

myencode (Intermediate _ l r) c=hangisi ('0':(myencode l c)) ('1':(myencode r c))
             where hangisi a b
			           |last b=='*'  =a
					   |otherwise=b
myencode (Leaf c _) c2
               |c==c2 =""
			   |otherwise="*"
----
data Crumb =LeftCrumb Integer HuffmanTree | RightCrumb Integer HuffmanTree

type BreadCrumbs=[Crumb]

mydecode _ [] _=[]

mydecode (Leaf a b) chars bs= a:(mydecode (goup (Leaf a b) bs) chars [])

mydecode (Intermediate i l r) (x:xs) bs
               |x=='0' =mydecode l xs ((LeftCrumb i r):bs)
			   |otherwise=mydecode r xs ((RightCrumb i l):bs)

goup t []=t			   
goup t ((LeftCrumb i r):bs)=goup (Intermediate i t r) bs
goup t ((RightCrumb i l):bs)=goup (Intermediate i l t) bs

decode tree eleman=mydecode tree eleman []

