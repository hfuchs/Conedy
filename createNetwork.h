

#ifndef __createNetwork
#define __createNetwork

#include "network.h"
#include <cmath>

#include "statisticsNetwork.h"


#ifndef EVENTCOUNT
#define EVENTCOUNT
#endif

#ifdef EVENTCOUNT
#include "eventHandler.h"
#endif

//#if OPENGL
//#include "glNetwork.h"
//#endif




namespace conedy
{


	/*!
	  \Brief Klasse zur zentralen Verwaltung von Parametern

	  Hier werden die einzelnen Netzwerke definiert (z.B. lattice, cycle, wattsStrogatz, cnnStd ...):

	  Dazu werden die Fuktionen aus network.h (z.B. AddEdge) verwendet.


	  Es werden folgende Standards verwendet:

	  int	networkElementType	(Nummer des NodeTypes - CNN, Rössler ... - wird automatisch in nodeBlueprint.h vergeben)
	  nodeKind	NodeKind	(Nummer der Nodeart - Input, Output ... - wird automatisch in nodeBlueprint.h vergeben)
	  nodeDescriptor	nodeNumber	(Nummer der Node - Wahl genau einer Node)

*/


	class createNetwork : public virtual network
	{

		public:

		static void registerStandardValues() 
		{ 
			params<baseType>::registerStandard ( _createNetwork_,"createNetwork_binary",0, 0.0 );
		}
		baseType inline writeBinary () { return p.getParams(0); }

		params<baseType> p;

			createNetwork() :p (_createNetwork_)   {};

			//! Erzeugt eine Kette von Knoten, bei der jeder mit den a nächsten Nachbarn verbunden ist.

			nodeDescriptor line ( unsigned int number, unsigned int a, nodeBlueprint *n = stdNode, edgeBlueprint *l=stdEdge);


			//! Erzeugt einen Ring mit <number> Kopien von *n, bei dem jeder Knoten mit den <a> nächsten Nachbarn nach links und recht verbunden ist. Edges sind Kopien von *l
			nodeDescriptor cycle ( int number, int a,nodeBlueprint *n = stdNode, edgeBlueprint *l= stdEdge );

			//! Erzeugt einen Ring mit zuerst <number1> Kopien von *n1, dann <number2> Kopien von *n2; bei dem jeder Knoten mit den <a> nächsten Nachbarn nach links und recht verbunden ist.
			nodeDescriptor cycleCluster (int number1, nodeBlueprint *n1, int number2, nodeBlueprint *n2, int a);

			//! Erzeugt ein Gitter mit x * y Knoten vom Typ *n. Zwei Knoten werden über einen Link vom Typ *l verbunden, falls ihr Abstand  kleiner sqrt(a) ist. Randknoten haben entsprechend weniger Verbindungen.
			nodeDescriptor lattice ( int sizex, int sizey, double a = 1.01, nodeBlueprint *n = stdNode, edgeBlueprint *l = stdEdge );

			//! Wie Gitter, jedoch werden die Ränder zyklisch verbunden (links mit rechts, oben mit unten).
			nodeDescriptor torus ( int sizex, int sizey, double a, nodeBlueprint *n, edgeBlueprint *l );			


			//! Erzeugt ein Gitter mit x * y Knoten vom Typ *n. Jeder Knoten wir mit seinen c nächsten Nachbarn verbunden. Gleichweit entfernte Nachbarn werden zufällig ausgewählt.
			nodeDescriptor torusRandomlyNearestNeighbours ( int sizex, int sizey, double c, nodeBlueprint *n, edgeBlueprint *l );

			//! Erzeugt ein Gitter der größe x * y aus streamInNodes, die alle aus der Datei s lesen. Funktioniert gut mit Dateien, die von observeAll erzeugt wurden
			nodeDescriptor streamInLattice ( int sizex, int sizey, string s );

			//! Zufallsgraph mit number Knoten vom Typ *n, bei dem je zwei mit der Wahrscheinlichkeit prop miteinander verbunden werden. Verbindungen sind vom Typ l
			nodeDescriptor randomNetwork ( nodeDescriptor number, double prop, nodeBlueprint *n = stdNode, edgeBlueprint *l = network::stdEdge );

			//! ein Netzwerk aus x * y Knoten vom Typ n
			nodeDescriptor beeWeb ( int x, int y, nodeBlueprint *n );

			//! Netzwerk mit number Knoten vom Typ *n, bei dem jeder mit jeden verbunden ist über einen Link vom Typ *l
			nodeDescriptor completeNetwork ( int number, nodeBlueprint *n =stdNode ,edgeBlueprint *l =stdEdge );               // number = Anzahl der Knoten


			void cnnStd ( int sizex, int sizey, string params, nodeBlueprint *n, edgeBlueprint *l );
			void cnnNeutral ( int sizex, int sizey, string params, nodeBlueprint *n,edgeBlueprint *l );
			void cnnStdLin ( int sizex, int sizey, string params, nodeBlueprint *n, edgeBlueprint *l );
			void cnnNeutralLin ( int sizex, int sizey, string params, nodeBlueprint *n, edgeBlueprint *l );


			//! OBSOLETE? Speichert die Verbindungsmatrix, des momentanen Netzwerk in die Datei s
//			void streamOutMatrix ( string s );



			//! Verbindet jeden Knoten der Art theNodeKind mit einem Rauschknoten, der double einkoppelt, die von der Funktion r zurückgegeben werden.
			void addGlobalNoise ( boost::function <double() > r, nodeKind theNodeKind = _dynNode_ );


			void addGlobalNoise ( function <double() > r ) { addGlobalNoise ( r, _dynNode_ ); }

			//! Normalisiert die Summe der eingehenden Kopplungsgewichte jedes Knotens au den Wert r
			void normalizeInputs (baseType r); 

			//			void createFromMatrix ( inStream & in, unsigned int size, nodeBlueprint *n );

			//! Fügt Kopien der Knoten aus nodes zum Netzwerk hinzu und verbindet mit Kopplungsgewichten aus der Matrix weights.
			//nodeDescriptor createFromMatrix ( vector <nodeBlueprint *> * nodes, vector <vector<baseType> > weights );

			nodeDescriptor createFromAdjacencyMatrix (string fileName, nodeBlueprint * n = stdNode, edgeBlueprint *e=stdEdge);

			//! Erstellt ein Netzwerk aus Knoten vom Typ n, und verbindet mit Kopplungsgewichten aus der adjacenzmatrix weights
			nodeDescriptor createFromMatrix ( vector <vector<baseType> > weights, nodeBlueprint *n );

			//! Erstellt ein Netzwerk aus Knoten vom Typ n und Verbindungen vom Typ l. Verbindungen werden aus der Datei fileName gelesen. Format: <Startknoten> <Zielknoten> <Verbindungsgewicht> \n
			nodeDescriptor createFromAdjacencyList ( string fileName, nodeBlueprint * n = stdNode, edgeBlueprint *l= stdEdge );


			void rewireWeights ( double prop ,boost::function<double () > r,nodeKind theNodeKind = _dynNode_ );

			//! Ersetzt Verbindungen mit Start- und Zielknoten der Art theNodeKind, durch ähnliche (kopierte) Verbindungen mit zufällig gewählten Start- und Zielknoten

			
//			void newire (double prop) { rewire(prop, _dynNode_, stdEdge);}

				// only consider edges which start and end at nodes of type n
			void rewire (double prop, nodeBlueprint *n = stdNode);
	

			void replaceEdges (double prop, edgeBlueprint *l = stdEdge, nodeBlueprint *n = stdNode);


			
void observeWithoutCheck (nodeDescriptor number, string s, edgeBlueprint *l);



			void rewireSourcePerTimestep ( double prop,function <baseType() > r, nodeKind theNodeKind = _dynNode_ );

			//! Ersetzt Verbindungen mit Start- und Zielknoten der Art theNodeKind, durch ähnliche (kopierte) Verbindungen mit zufällig gewählten Zielknoten und unverändertem  Startknoten
			void rewireTarget ( double prop ,nodeKind theNodeKind = _dynNode_ );


			void rewireTargetUndirected ( double prop, nodeKind theNodeKinde = _dynNode_ );

			void rewireUndirected (double prop, nodeKind theNodeKind = _dynNode_ ); // Rewire mit einem ungerichteten Netzwerk im Nachhinein


			//! Ersetzt Verbindungen mit Start- und Zielknoten der Art theNodeKind, durch ähnliche (kopierte) Verbindungen mit zufällig gewählten Startknoten und unverändertem  Zielknoten
			void rewireSource ( double prop ,nodeKind theNodeKind = _dynNode_ );


			void observeEventTimes( string fileName,nodeDescriptor eventNumber );


		


			void observeTime ( string s );

			//! observiert den Knoten number über eine Edge vom Typ l und  schreibt in die Datei s
			void observe (  nodeDescriptor number, string s,edgeBlueprint * l  = stdEdge);



			void observeEventCounter ( string s, unsigned int signature);

			//! wie oben. Phasen werden von Edges vom Typ l übergeben.
			void observeMeanPhase ( string s, edgeBlueprint *l );


			void observeMeanPhase ( string s );


			//! wie oben mit links vom Typ l
			void observeMean ( string s, edgeBlueprint *l );

			void observeEvent (string s, nodeDescriptor signature);


			//! wie oben allerdings wird die Phasenkohärenz r der States s_i weggeschrieben: r = 1/N \sum\limits_i exp( 2 * PI * s_i). Phasen gehen von 0 bis 1 !!! TODO: vielleicht von streamOutNode erben ??


			//! wie oben. Phasen werden von Edges vom Typ l übergeben.
			void observeAllPhaseCoherence ( string s, edgeBlueprint *l );

//			void observePhaseCoherence ( string s );

//			void observePhaseCoherence ( string s, nodeBlueprint *n = stdNode,  edgeBlueprint *l= stdEdge );
			
//			void observePhaseCoherence ( nodeDescriptor lower, nodeDescriptor upper, string s,  edge *l );
	

			void observePhaseCoherence ( string s, edgeBlueprint *l = stdEdge, nodeBlueprint *n = stdNode, nodeDescriptor lower = 0, nodeDescriptor upper = numeric_limits<nodeDescriptor>::max());



			void observePhaseCorrelation ( string s, nodeBlueprint *n);
			void observePhaseDistance ( string s, nodeBlueprint *n);


			void addRandomEdgesDegreeDistribution ( function <double () > r, edgeBlueprint *l = stdEdge );


			//! Fügt einen Knoten vom Typ streamOutNode hinzu, der in die Datei s schreibt. Der Knoten erhält eine stdEdge zu jedem Knoten vom Typ _dynNode_. und schreibt somit die Summe aller States weg.
			void observeMean ( string s );

			//! observiert den Knoten number mit einer stdEdge und schreibt in die Datei s.
//			void observe ( string s, nodeDescriptor number );

			//!
//			void addRandomEdges ( double meanOutDegree )
//			{
//				addRandomEdges ( meanOutDegree, network::stdEdge );
//			}
			void addRandomEdges ( double meanOutDegree, edgeBlueprint * l = stdEdge );


			template <typename RANDOM>
				void randomOutDegreeDistribution ( int number, RANDOM &r, nodeBlueprint *n );

			template <typename RANDOM>
				void randomInDegreeDistribution ( int number, RANDOM &r, nodeBlueprint *n );


			//			template <typename SIZE>
			//			void streamInBinary ( inStreamBinary in, char flags , SIZE );
			void streamInBinary ( string s );

			//			template <typename SIZE>
			//			void streamOutBinary ( outStreamBinary out, char flags , SIZE );
			void streamOutBinary ( string s, char flags = 24 );

			//			void addSuperAttractiveNode (nodeBlueprint *n, nodeKind theNodeKind = _dynNode_);
			//			void addSuperAttractiveNode (nodeBlueprint *n, nodeKind theNodeKind, edge *l);

			//			void addSuperNode ( nodeBlueprint *n );
			//			void addSuperNode ( nodeBlueprint *n, edge <baseType> *l);
			//			void addSuperNodeBidirectional ( nodeBlueprint *n, edge *l);

			void addEnterNode ( string s );

			void observeHidden ( string s, int number );

			void observeAll ( string s, edgeBlueprint *l = stdEdge);

			void observeAllHiddenVariables ( string s );

			void observeRandom ( string s );

			template <typename NODETYPE>
				void dummy();




			static bool cmp2d ( pair< int, int > a, pair< int, int > b )
			{

				return ( a.first * a.first + a.second * a.second ) < ( b.first * b.first + b.second * b.second );

			}


	};	// ENDE class createNetwork


	//
	// #### Deklarationen einzelner Netzwerke: ######################
	// (z.B. lattice, cycle usw...)
	//






}
#endif