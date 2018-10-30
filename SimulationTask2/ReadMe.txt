1. Copy the zip file from local computer to Eos using below Command. Give the password when prompted.

	pscp /Directory/SimulationTask2.zip unityid@remote.eos.ncsu.edu:

2. Go the Eos and unzip the file using below command.

	unzip SimulationTask2.zip

3. Go to Folder SimulationTask2

	cd SimulationTask2

4. Compile the file using below command.

	g++ SimulationTask2.cpp -o sim

5. Edit the values in "SimulationTask2Input.txt" file to give the input. Input in the file is in below order.

	30 - N
	1 - Dh
	2 - Dl
	10 - Mean Service time in infinite server queue.
	1.5 - Mean Service time in client queue.
	3 - Tl
	3 - Th

6. Run the simulation using below command.

	./sim

7. Check the output in the file named: "SimulationTask2Output.txt"