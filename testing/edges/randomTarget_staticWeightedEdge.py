import conedy as co

net = co.network()







firstNode = net.addNode(co.roessler())
secondNode = net.addNode(co.roessler())

net.addEdge (firstNode,secondNode, co.randomTarget_staticWeightedEdge (2, 100, 0.7) )


net.printNodeStatistics()

