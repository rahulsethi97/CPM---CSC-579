1. Copy the zip file from local computer to Eos using below Command. Give the password when prompted.

	pscp /Directory/RandomNumberTester.zip unityid@remote.eos.ncsu.edu:

2. Go the Eos and unzip the file using below command.

	unzip RandomNumberTester.zip

3. Go to the folder RandomNumberTester;

	cd RandomNumberTester

3. Compile the file using below command.

	g++ ChiSquareTest.cpp FrequencyTest.cpp RunsTest.cpp RandomNumberTester.cpp -o test


5. Run the Test using below command.

	./test

6. Give the number of random numbers you want to generate and check the output.
