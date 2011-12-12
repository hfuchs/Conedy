import conedy as co
net = co.network()
co.set ("roessler_a", 0.22)
co.set ("roessler_b", 0.1)
co.set ("roessler_c", 8.5)
r1 = net.addNode(co.roessler())
r2 = net.addNode(co.roessler())
r3 = net.addNode(co.roessler())
net.setParam(r1, "roessler_omega", 1.02)
net.setParam(r2, "roessler_omega", 1.0)
net.setParam(r3, "roessler_omega", 0.98)
net.randomizeStates (co.roessler(), co.uniform (-10.0, 10.0),co.uniform (-5.0, 5.0), co.uniform (-0.5, 1.5))
net.addEdge(r1, r2, co.weightedEdge(0.075))
net.addEdge(r2, r1, co.weightedEdge(0.075))
net.addEdge(r1, r3, co.weightedEdge(0.075))
net.addEdge(r3, r1, co.weightedEdge(0.075))
net.evolve(0.0, 100.0)
net.observeTime("roessler.dat")
net.observe(r1, "roessler.dat", co.component(1))
net.observe(r2, "roessler.dat", co.component(1))
net.observe(r3, "roessler.dat", co.component(1))
co.set("samplingTime", 0.01)
net.evolve(100.0, 200.0)
