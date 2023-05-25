programul citeste din c.in si afla obiectivele \
creaza o lista cu toate elementele din fisierul d.in\
elimina din lista echipe pana cand raman 2^n cea mai apropiata puetre fata de cate elemnete erau in lista anterioara\
incepe sa treca prin fiecare bracket al lanParty \
iar in momentul in care raman 8 echipe aceastea se stockeaza intr-un BST updatanduse cu valorile corecte\
se poate printa BST in mod neordonat doar dupa cum a fost creat in mod initial\
se ordoneaza dup amodelul AVL si se printeaza echipele de pe height=2\

RunBracket - rualeza un bracket al meciului salvand echipele catigatoare si cele care au pierdut\
playOutLanParty/playOutLanPartyPrint -sunt 2 variante a aceleasi functii care ruleaza intregul turneu si il printeaza sau nu salvand ultimele 8 echipe intru BST\
InitialCulling - ia o lista de echipa si elimina din ea pana cand sunt 2^n\
addToFinalist aduaga in copacul de finalisti\
createGameList/createGameListStack  - creaza o caoda cu meciurile unui bracket ori dintro lista ori stack\
