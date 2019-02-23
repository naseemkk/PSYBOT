# PSYBOT
It's a self navigating robot which can patrol a given area in a predefined path and help the passengers to reach their desired destination in airports or similiar infrastuctures.

The `bot` is fed with images of wanted people from some criminal database which is used by the `bot` to identify them and turn on alarm in patrolling mode.

Burn `guidance.c` code into the arduino to use the PSYBOT in guidance mode and `patrolling.c` to use the bot in patrolling mode.

#### Face Recognition 
To create the dataset of a person, run the `createdataset.py` file

To train the system with the dataset obtained or stored, run the `training.py` file

To recognise a trained face run the `facerecognition.py` file, which gives an alert on recording a matching face in the building.
