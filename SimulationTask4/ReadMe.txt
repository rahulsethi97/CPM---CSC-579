** Code takes around 4-5 minutes to execute for one set of inputs **

1. Copy the zip file from local computer to Eos using below Command. Give the password when prompted.

	pscp /Directory/SimulationTask4.zip unityid@remote.eos.ncsu.edu:

2. Go the Eos and unzip the file using below command.

	unzip SimulationTask4.zip

3. Go to Folder SimulationTask4

	cd SimulationTask4

4. Compile the file using below command.

	g++ RunSim4.cpp SimulationTask4.cpp -o sim4

5. Edit the values in "SimulationTask4Input.txt" file to give the input. Input in the file is in below order.

	90000 - N
	1 - Dh
	2 - Dl
	10 - Mean Service time in infinite server queue.
	1.5 - Mean Service time in client queue.
	3000 - Batch Size

6. Run the simulation using below command.

	./sim4

7. Check the output.