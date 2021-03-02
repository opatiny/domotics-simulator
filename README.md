# A C Project: Basic domotics simulator

Link to the GitHub: [https://github.com/opatiny/S1-INFO1/tree/master/project](https://github.com/opatiny/S1-INFO1/tree/master/project)

Refer to the [changelog](./CHANGELOG.md) to know the enhancement made in V2 of the project.

## Running the project

At the top level of the project, use the following command to run:
```bash
./run.sh
```

If desired, you can modify the user options in the `Scheduler.c` (lines 38 to 42):

```cpp
USER_OPTIONS options = {.nbTics = 24,               // number of tics to do
                        .ticLength = 60 * 60,       //  in seconds
                        .weather = LAUSANNE_WINTER, // can also be LAUSANNE_SUMMER
                        .showOutputData = 0,        // 1 or 0
                        .showControlValues = 1};    // 1 or 0
```

After you run the previous command, check the results of the simulation by inspecting the controllers values stored in the files of the `logs` folder.

## Testing the code

To use our custom C testing environment, use the `tests.sh` script as follows:
```bash
./test.sh
```

It will print wether all the tests in the project pass or fail.

## Context

The goal is to implement a simulator of an appartment, which consists of two rooms. Additionally, an aquarium is placed in room 1. They are two external variables: luminosity and temperature. We will have to compute the variation of the temperature and luminosity inside of the rooms. Based on these "measurements", the temperature of the rooms will have to be controlled in order to ensure it is comfortable. The luminosity in room 1 will affect the algea in the aquarium, and therefore the amount of oxygen in the water, and the PH. Again, the PH ought to be controlled.

The simulated measurements of the luminosity and temperature should be stored in order to manipulate this data and produce statistics. We will first store the data in arrays, then, we will learn to store it in external files, which are permanent. This will allow the statistics to be computed after the completion of the simulation.

Each function of the program is called at different times, but some can run "simultaneously". In other words, we will simulate some multithreading. To achieve that in C, we will have to implement a super-function called the `Scheduler`, which handles the functions calls.

Throuought the project, a top-down approach is prefered.
