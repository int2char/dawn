/*attention:
allocatoradasasdasdasdasdasas
graph dependent*/
#ifndef CONSTH
	#define CONSTH
	#ifndef NODE
		#define NODE 50
	#endif
	#ifndef Task
		#define Task 300
	#endif
	#ifndef EDge
		#define EDge 304
	#endif
	#ifndef CAPACITY
		#define CAPACITY 100
	#endif
	#ifndef TYPE
		#define TYPE "BA"
	#endif
	#ifndef GRAPHTYPE
		#define GRAPHTYPE 1
	#endif
	#ifndef GANOEX
		#define GANOEX -1
	#endif
	#ifndef INPUTFILE
		#define INPUTFILE "./"
	#endif
	#ifndef EXPIRE
		#define EXPIRE 600000
	#endif
	#define PERB ((Task>EDge)?Task:EDge)
	#define INFHOPS 50
	#define Deep 300
	#define loop 30
	#define TD 500
	#define loomore 30
	#define FROM 0
	#define STATMAX 100*POP
	#define LAGPFILE "./data/iteration.txt"
	#define LAGSFILE "./data/iteration.txt"
	#define GAPFILE "./data/iteration.txt"
	#define GASFILE "./data/iteration.txt"
	#define ANSWERS "./data/answers.txt"
    #define TOPFILE "Graph.txt"
	#define ROUTFILE "data.txt"
	#define FLOWFILE "service.txt"
	#define INFOFILE "./data/info.txt"
	#define DATAFILE "./data/all_data.txt"
	#define FLOWVARRY "./data/flow_varry.txt"
	#define EDGE 1500
	#define POP 5000
	#define ALPHA 500
	#define Beta 1000
	#define Gama 3500
	#define ROD 30
#endif
