import copy
from string import ascii_uppercase

FAILURE = -1

alphabet=[]
howmany=1
chm=1

class Variable:
    def __init__(self,_name):
        self.name=_name
    def type(self):
        return 'V'
    def __eq__(self, other):
        if other.type()==self.type() and other.name==self.name:
            return True
        return False


class Constant:
    def __init__(self,_name):
        self.name=_name
    def type(self):
        return 'C'
    def __eq__(self, other):
        if other.type()==self.type() and other.name==self.name:
            return True
        return False
class Function:
    def __init__(self,_name):
        self.name=_name
        self.args=[]
    def type(self):
        return 'F'
    def addArg(self,arg):
        self.args.append(arg)
    def __eq__(self, other):
        if other.type()==self.type() and other.name==self.name and len(other.args)==len(self.args):
            for arg in self.args:
                exists=False
                for argO in other.args:
                    if (arg == argO):
                        exists=True
                        break
                if exists == False:
                    return False
            return True
        return False

class Predicate:
    def __init__(self,_name,_isNeg):
        self.name=_name
        self.args=[]
        self.isNeg=_isNeg
    def type(self):
        return 'P'
    def addArg(self,arg):
        self.args.append(arg)
    def __eq__(self, other):
        if other.type()==self.type() and other.name==self.name and len(other.args)==len(self.args) and self.isNeg == other.isNeg:
            for arg in self.args:
                exists=False
                for argO in other.args:
                    if (arg == argO):
                        exists=True
                        break
                if exists == False:
                    return False
            return True
        return False
    def eq(self, other):
        if other.type()==self.type() and other.name==self.name and len(other.args)==len(self.args):
            for arg in self.args:
                exists=False
                for argO in other.args:
                    if (arg == argO):
                        exists=True
                        break
                if exists == False:
                    return False
            return True
        return False

class Clause:
    cn=0
    def __init__(self,_predicates,_p1=None,_p2=None):
        self.id=self.cn
        self.cn=self.cn+1
        self.predicates=copy.deepcopy(_predicates)
        self.p1=copy.deepcopy(_p1)
        self.p2=copy.deepcopy(_p2)
    def addPredicate(self,predicate):
        self.predicates.append(predicate)
    def __eq__(self, other):
        if len(other.predicates) == len(self.predicates):
            for predicate in self.predicates:
                exists=False
                for op in other.predicates:
                    if (predicate == op):
                        exists=True
                        break
                if exists == False:
                    return False
            return True
        else:
            return False
#bu degil
def contains(e1,e2):
    if e2.type()=='P' or e2.type()=='F':
        for arg in e2.args:
            if contains(e1,arg) == True:
                return True
    elif e2.type()=='V' and e1.name == e2.name:
        return True

    return False
#bu degil
def change(_e1,theta):
    '''
    global chm
    print "change",e1,theta,chm
    chm=chm+1
    '''
    e1=e1=copy.deepcopy(_e1)
    if len(theta)==0 or e1.type()=='C':
        return e1
    if e1.type()=='F' or e1.type()=='P':
        for i,arg in enumerate(e1.args):
            e1.args[i]=change(arg,theta)
        return e1
    elif e1.type()=='V':
        L=[t[1] for i, t in enumerate(theta) if t[0] == e1]
        if len(L)!=0:
            return L[0]
        else:
            return e1
#bu degil
def add(theta,theta2):
    if len(theta2)!=0:
        for i,sub in enumerate(theta):
            theta[i]=(sub[0],change(sub[1],theta2))
        theta.append(theta2[0])


#bu degil
def unify1(_e1,_e2):
    e1 = copy.deepcopy(_e1)
    e2 = copy.deepcopy(_e2)
    if e1.type()!='C' or e1.type()!='V':
        tmp=e2
        e2=e1
        e1=tmp
    if e1 == e2:
        return []
    if e1.type()=='V':
        if contains(e1,e2):
            return FAILURE
        return [(e1,e2)]
    if e2.type()=='V':
        return [(e2,e1)]
    return FAILURE


#bu degil
def unify(_e1,_e2):
    '''
    global howmany
    print e1,e2,howmany
    howmany=howmany+1
    '''
    e1=copy.deepcopy(_e1)
    e2=copy.deepcopy(_e2)
    if e1.type()=='V' or e2.type()=='V' or e1.type()=='C' or e2.type()=='C':
        return unify1(e1,e2)
    elif e1.name != e2.name or len(e1.args) != len(e2.args):
        return FAILURE

    theta=[]
    for i in range(0,len(e1.args)):
        theta2=unify(change(e1.args[i],theta[:]),change(e2.args[i], theta[:]))
        if theta2==FAILURE:
            return FAILURE
        else:
            add(theta,theta2)
    return theta

def tautology(clause):
    n=len(clause.predicates)
    if n==0:
        return False
    else:
        pairs = [(clause.predicates[i], clause.predicates[j]) for i in range(n) for j in range(i + 1, n)]
        for (pi, pj) in pairs:
            if ((pi.isNeg is not pj.isNeg)) and pi.eq(pj):
                return True
        return False

#bu degil
def issubset(new,clauses):
    if len(new)==0 :
        return True
    elif len(new)>len(clauses):
        return False
    else:
        for cn in new:
            exists=False
            for cc in clauses:
                if cn == cc:
                    exists=True
                    break
            if exists==False:
                return False
        return True
#bu degil
def pInS(a):
    s2=""
    if a.type()=='C' or a.type()=='V':
        return a.name
    elif a.type()=='F' or a.type()=='P':
        if a.type()=='P' and a.isNeg==True:
            s2="~"
        s2= s2+a.name + "("
        n=len(a.args)
        for i,arg in enumerate(a.args):
            s2 = s2 + pInS(arg)
            if i != n-1:
                s2=s2+","
        s2=s2+")"
    return s2
#bu degil
def cInS(c):
    s2=""
    n = len(c.predicates)
    if n==0:
        return "empty_clause"
    for i, p in enumerate(c.predicates):
        s2 = s2 + pInS(p)
        if i != n - 1:
            s2 = s2 + ","

    return s2
#bu degil
def printSolution(clause):
    s=""
    if clause.p1!=None and clause.p2!=None:
        s=cInS(clause.p1) + "$" + cInS(clause.p2) + "$" + cInS(clause)
        if clause.p1.p1!=None and clause.p2.p1!=None:
            s=printSolution(clause.p1) + "\n" +printSolution(clause.p2) + "\n" +s
        elif clause.p1.p1!=None:
            s = printSolution(clause.p1) + "\n" + s
        elif clause.p2.p1!=None:
            s = printSolution(clause.p2) + "\n" + s
    return s

#bu degil
def variables(pf):
    vars=[]
    if pf.type()=='C':
        return vars
    elif pf.type()=='V':
        if pf not in vars:
            v=copy.deepcopy(pf)
            vars.append(v)
        return vars
    else:
        for arg in pf.args:
            rvs=variables(arg)
            for rv in rvs:
                if rv not in vars:
                    _rv = copy.deepcopy(rv)
                    vars.append(_rv)
        return vars
#bu degil
def constants(pf):
    vars = []
    if pf.type() == 'V':
        return vars
    elif pf.type() == 'C':
        if pf not in vars:
            v = copy.deepcopy(pf)
            vars.append(v)
        return vars
    else:
        for arg in pf.args:
            rvs = constants(arg)
            for rv in rvs:
                if rv not in vars:
                    _rv = copy.deepcopy(rv)
                    vars.append(_rv)
        return vars
#bu degil
def subsumes(c,d):
    W=[]
    cs=[]
    v=[]
    theta=[]

    for predicate in c.predicates:
        for constant in constants(predicate):
            if constant not in cs:
                cs.append(constant)

    for _predicate in d.predicates:
        predicate=copy.deepcopy(_predicate)
        predicate.isNeg=not (predicate.isNeg)
        for constant in constants(predicate):
            if constant not in cs:
                cs.append(constant)
        for variable in variables(predicate):
            if variable not in v:
                v.append(variable)
        W.append(Clause([predicate]))

    _alphabet=copy.deepcopy(alphabet)
    n=len(cs)
    if n!=26:
        for var in v:
            for _c in _alphabet:
                if _c not in cs:
                    theta.append((var,_c))
                    _alphabet.remove(_c)
                    break

    for clause in W:
        for predicate in clause.predicates:
            predicate=change(predicate,theta)

    U=[c]
    while True:
        for clause in U:
            if len(clause.predicates)==0:
                return True
        Unext=[]
        for cu in U:
            for cw in W:
                resolvents=pl_resolve(cu,cw)
                Unext=Unext+resolvents
        if len(Unext)==0:
            return False
        U=Unext





#bu degil
def pl_resolution(KB):
    clauses=KB[:]
    new = []
    while True:
        n = len(clauses)
        pairs = [(clauses[i], clauses[j]) for i in range(n) for j in range(i+1, n)]
        for (ci, cj) in pairs:
            resolvents = pl_resolve(ci, cj)
            for resolvent in resolvents:
                if len(resolvent.predicates)==0:
                    ###############
                    return "yes\n"+printSolution(resolvent)
                elif resolvent not in new:
                    readyToNew=True
                    if tautology(resolvent)==True:
                        readyToNew=False
                    else:
                        for clause in clauses:
                            if subsumes(clause,resolvent):
                                readyToNew=False
                                break
                    if readyToNew==True:
                        new.append(resolvent)
        if issubset(new,clauses):
            return "no"
        for c in new:
            if c not in clauses:
                clauses.append(c)
#bu degil
def removeall(p,_c,theta):
    newPs=[]
    c=copy.deepcopy(_c)
    for cp in c.predicates:
        if (cp == p) ==False:
            sp=change(cp,theta)
            newPs.append(sp)
    return newPs




#bu degil
def pl_resolve(ci, cj):
    """Return all clauses that can be obtained by resolving clauses ci and cj.
    pl_resolve(to_cnf(A|B|C), to_cnf(~B|~C|F))
    [(A | C | ~C | F), (A | B | ~B | F)]
    """
    clauses = []
    for di in ci.predicates:
        for dj in cj.predicates:
            if di.name==dj.name:
                if di.isNeg is not dj.isNeg:
                    theta=unify(di,dj)
                    if theta!=FAILURE:
                        dnew = removeall(di, ci,theta) + removeall(dj, cj,theta)
                        clauses.append(Clause(dnew,ci,cj))

    return clauses
#bu degil
def builder(clauseString):
    predicates=[]
    queue=[]
    paranthesis=[]
    isNeg=False
    l=len(clauseString)
    for i,ch in enumerate(clauseString):
        #print queue
        #print paranthesis
        #print ch
        if ch.isalpha():
            if len(queue)==0:
                queue.append(Predicate(ch, isNeg))
                if isNeg:
                    isNeg=False
                #print queue
            elif clauseString[i+1] == '(':
                queue.append(Function(ch))
            else:
                if ch.isupper():
                    tmp=queue.pop()
                    tmp.addArg(Constant(ch))
                    queue.append(tmp)
                else:
                    tmp = queue.pop()
                    tmp.addArg(Variable(ch))
                    queue.append(tmp)
                #print queue
        elif ch=='~':
            isNeg=True
        elif ch==',':
            continue
        elif ch=='(':
            paranthesis.append(ch)
        elif ch==')':
            del paranthesis[-1]
            if len(paranthesis)==0:
                predicates.append(queue.pop())
                #clause.addPredicate(queue.pop())
            else:
                #print queue
                tmp=queue.pop()
                tmp2=queue.pop()
                tmp2.addArg(tmp)
                queue.append(tmp2)
    clause = Clause(predicates)
    return clause
#bu degil
def main():
    for uc in list(ascii_uppercase):
        alphabet.append(Constant(uc))
    KB=[]
    G=[]
    f = open('the2.inp', 'r')
    output = open("the2.out", 'w')
    numOftasks = int(f.readline().strip())
    #print "numOftasks",numOftasks
    for task in range(0, numOftasks):
        numBG = f.readline().strip().split(' ')
        #print numBG
        for numB in range(0, int(numBG[0])):
            clause=builder(f.readline().strip())
            KB.append(clause)
        for numG in range(0,int(numBG[1])):
            clause = builder(f.readline().strip())
            KB.append(clause)
        output.write(pl_resolution(KB))

    output.close()

if __name__ == '__main__':
    main()