from rdflib import *
from SPARQLWrapper import *
from rdflib.namespace import FOAF

g = Graph()
g.parse("foaf.n3", format="n3")

#print len(g)

books=[]

def sparqlfunc(endpoint,query):
	resultlist=[]
	sparql = SPARQLWrapper(endpoint)
	sparql.setQuery(query)
	sparql.setReturnFormat(JSON)
	results = sparql.query().convert()
	for result in results["results"]["bindings"]:
		resultlist.append(result["label"]["value"])
	return resultlist

def sparqlfunc2(endpoint,query):
	resultlist=[]
	sparql = SPARQLWrapper(endpoint)
	sparql.setQuery(query)
	sparql.setReturnFormat(JSON)
	results = sparql.query().convert()
	for result in results["results"]["bindings"]:
		resultlist.append((result["label"]["value"],result["label2"]["value"]))
	return resultlist


for s,p,o in g.triples( (None, FOAF.topic_interest, None) ):
	query="""PREFIX k: <http://www.yso.fi/onto/kaunokki#> 
			 PREFIX skos: <http://www.w3.org/2004/02/skos/core#>
			 SELECT ?label ?label2 
			 WHERE { ?label k:asiasana <"""+ str(o) +"""> . 
			 ?label skos:prefLabel ?label2.}"""
	books=sparqlfunc2("http://ldf.fi/kirjasampo/sparql",query)

	query="PREFIX skos: <http://www.w3.org/2004/02/skos/core#> SELECT ?label WHERE {?label skos:broader <"+str(o)+">.}"
	interests=sparqlfunc("http://ldf.fi/koko/sparql",query)
	for interest in interests:
		query="""PREFIX k: <http://www.yso.fi/onto/kaunokki#> 
				 PREFIX skos: <http://www.w3.org/2004/02/skos/core#>
				 SELECT ?label ?label2 
				 WHERE { ?label k:asiasana <"""+ str(interest) +"""> . 
			 	 ?label skos:prefLabel ?label2.}"""
		books=books + sparqlfunc2("http://ldf.fi/kirjasampo/sparql",query)

counter=0
for book in books:
	if counter==10:
		break
	print book[1]
	counter=counter+1


for person in g.subjects(FOAF.topic_interest, None):
	print person
	for book in books:
   		g.add( (person,FOAF.interest,URIRef(book[0])) )
   		#print "a"
g.serialize("foaf2.n3",format='n3')