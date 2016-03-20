# Models
### Dynamic Models
When going about doing a simulation, a common model is one based on a dynamical system of equations described by differential equations. These models are the ones that require numerical integration in time with approaches like Euler or Runge-Kutta integration.

### Discrete Models
These models represent discrete events in time. This can be, for example, a discrete GPS update for a missile, a discrete time step at which to force dynamic models to integrate, and even a discrete event to write data to a file at a certain time interval. These models have their own unique importance in most simulation environments and can be exploited in this framework.

# Time
### Time Representation
Within the framework, time has been designed to be kept and incremented in the most precise fashion possible. It is common knowledge that working with floating point numbers will result in round off errors, especially when one floating point number is much larger than the other. In the simulation, since it is likely we may be doing operations with large times against small time steps, round off errors are sure to occur.

To ensure a precise time step is taken, time will be kept in terms of a _Mixed Fraction_. Then when precise, floating point values for time are needed, the Mixed Fraction will be converted to a floating point value for use in computation.

### Event Tracking in Simulation
Currently in the framework, the items that are required to be tracked in time are all discrete time events. At each discrete event, any and all `Dynamic` models are updated via numerical time integration. Thus, it is important to efficiently and accurately keep track of these discrete time events. 

This framework automatically handles the discrete event handling via a class called a Scheduler, which is essentially a Minimum Heap data structure popping the next time event everytime a simulation time step needs to be taken. 

For a user of the framework, however, you just need to add the discrete models to the simulation class, and it will do the hard work for you.

# Monte Carlo Simulation Capability
### Random Number Generation
This framework is built to have a centralized random number generator within the `Simulator` class structure. And since each Dynamic and Discrete model maintains a reference to it's parent Simulation object, it is able and should utilize this central random number generator when variation is needed inside the models for the simulation.

### Monte Carlo Runs
This framework also has a simple layer built into it to allow for multiple runs of the same simulation, allowing a simulation to utilize the variation created from the random number generator to generate a Monte Carlo set of varying simulation results based on different initial seeds for each Monte Carlo simulation.

While the default simulation structure sets the number of Monte Carlo runs to 1, since not all simulations need to be run in a Monte Carlo fashion, a user is able to modify this variable in their subclassed **Simulator** class.

# Simulation Data Output
### Simulation History Data Output
When one generates a simulation, it may be desireable to capture all the time history for a set of variables through he lifetime of each simulation, even when doing multiple Monte Carlo simulation runs. Fortunately, the framework has a solution built for this problem.

A given model, whether it is a `Dynamic` or `Discrete`, has a virtual method that can be defined when subclassing your own model known as `setupPrintData()`. This method is used by the simulation's backbone simLoop method to connect up data a user wishes to have outputted into a sim history data file. A simple example of this method might be the following for a `Dynamic` model:

```c
virtual void setupPrintData() {
  parent->addVariableToPrint(&state[0], "X-Position"); //save particle position
  parent->addVariableToPrint(&state[1], "X-Velocity"); //save particle velocity
}
```

The `parent` variable is already a part of each model, and the `addVariableToPrint` method is the method to use when adding a new variable to the sim history output file. Once you define this virtual method for a given model, you will obtain the resulting output file that you desire!

### End Game Simulation Output
There is no predefined code to allow for you to just save off data or print information to the terminal at the end of a simulation run, but pieces are in place that can help to encapsulate this functionality and get the results you want in the `simLoop`. 

There are two methods in a `Simulator` subclass that you might want to edit. The first virtual method is the `finalizeMonteCarloRun()` method. By overwriting this method, you are specifying actions to take place after a given Monte Carlo run has completed. An example of something you might do is print a simple status update to the terminal or save off some info to a file.

The second virtual method is the `finalize()` method. This method is run after all of the simulations, Monte Carlo sims included, has completed. Often, there may be no need to overwrite this method. But in the event there is some computation that a user wants to be run just before the sim finishes, this method is the place to do it.

Examples of these two methods might be the following:

```c
virtual void finalizeMonteCarloRun(){
  printf("Hey, I finished the %ith run!\n",numRuns);
}

virtual void finalize(){
  printf("Finished the Simulation!\n");
}
```

# Defining the Completion of the Simulation
Not all simulations are created equal and often simulations have different completion criteria. Some simulations use simple completion criteria, such as stopping the simulation when a time limit is hit. Others, such as simulating a missile flight or robot maneuver, might have the completion of a simulation depend on where the objects being simulated end up spacially. 

Due to these potentially very different completion criterias, the framework has defined a virtual method that can be overwritten to define what will make a given simulation be done. The method to overwrite in the `Simulator` subclass is called `finishedSimulation()` and it returns a boolean. 'true' means the simulation is complete, 'false' means it isn't.

A simple example of this method might be the following:

```c
virtual bool finishedSimulation() const {
  return getCurrentTime() >= 10.0; 
}
```

# Adding Models to a Simulator
Now the approach to adding a given model to a subclassed `Simulator` is practically the same for both `Dynamic` and `Discrete` models. The general idea is that this work will need to be done in an overwritten version of the `linkModelsToSim()` method, which is a part of the `Simulator` subclass. To help you see how it might look, here is an example:

```c
virtual void linkModelsToSim(){
  addDiscrete(&discreteModel, evalsPerSecond);
  addDynamics(&dynamicModel);
}
```

This piece of code shows how simple it is to add models to the `Simulator`. One just needs to use the built in `addDiscrete` and `addDynamics` methods and then everything will be put together as desired. One note is that the `addDiscrete`'s second input is the frequency a `Discrete` model is expected to be run in the simulation.

# Getting Input from External Files
### Add Configuration File to Simulation
At the moment, there is a simple system in place to setup configuration files that can be read in at runtime for a given program. All one needs to do is provide the path to some configuration file and call the `addConfigFile` method of the `Simulator` class. An example of this might be the following:

```c
Simulator sim;
sim.addConfigFile("someFile.cfg");
sim.addConfigFile("../heresAnotherFile.cfg");
```

The `Simulator` then ensures the necessary variables are parsed and brought into a hash table for quick look up. Currently, the config files are expected to only have numeric inputs, though this will be changed down the road. The following is an example of a working config file:

```python
# Here's the start of the Config File
# Config file #1
variable1: 12.3
variable2: 4.0     # comments after a variable is okay
variable3: 9.27    # make sure to use a : after the variable name

# Here's the last variable
willDance: 1.0
willEat:   0.0

# Here's some vectors
vec1: [1, 2, 3, 4] #equates to [1, 2, 3, 4]
vec2: [1:5, 6, 8 ] #equates to [1, 2, 3, 4, 5, 6, 8]
vec3: [12:10, 5,2] #equates to [12, 11, 10, 5, 2]
vec4: [0:1.1:5.5,7]#equates to [0, 1.1, 2.2, 3.3, 4.4, 5.5, 7]
vec5: [3.3:-1.1:0] #equates to [3.3, 2.2, 1.1, 0]

# Here's some words
name: Christian
filepath: /some/path/here/file.txt
```

By writing a config file with the appropriate syntax, the `Simulator`'s parser will take care of getting the variables parsed.

### Retrieve Configuration Variable Value
To retrieve the value of a given variable, one just needs to use the `get` method of the `Simulator` class. An example of how to use this method can be seen below:

```c
typedef std::vector<double> Vector;
typedef std::String String;

Simulator sim;
double variable1  = sim.get<double>("variable1");
bool willEat      = sim.get<bool>("willEat");
Vector vec        = sim.get<std::vector<double>>("vec4");
String name       = sim.get<std::string>("name");
```

Since a given model, be it `Dynamic` or `Discrete`, has a reference to it's parent `Simulator`, any custom model's can easily call the `get` method to use input variables for the models! It is recommended you add config files to the sim before you call the sim's `initialize()` method to ensure the data exists before any models need to grab it for use.