1. Copy the zip file from local computer to Eos using below Command. Give the password when prompted.

	pscp /Directory/SimulationTask2.zip unityid@remote.eos.ncsu.edu:

2. Go the Eos and unzip the file using below command.

	unzip SimulationTask3.zip

3. Go to Folder SimulationTask2

	cd SimulationTask3

4. Compile the file using below command.

	g++ SimulationTask3.cpp -o sim3

5. Edit the values in "SimulationTask2Input.txt" file to give the input. Input in the file is in below order.

	90000 - N
	1 - Dh
	2 - Dl
	10 - Mean Service time in infinite server queue.
	1.5 - Mean Service time in client queue.
	6 - Tl
	6 - Th
	3000 - Batch Size

6. Run the simulation using below command.

	./sim3

7. Check the output in the file named: "SimulationTask3Output.txt"