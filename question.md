

In one apartment building, which holds 500 people, after an ice storm, the doors are frozen shut and everyone is trapped in the building. One apartment's dwellers suddenly become zombies. The zombies go rampaging through the building, turning the other apartment dwellers into zombies.

Fortunately, some (9) people know how to kill zombies, and they are able to teach the other people who live in the apartment building. The chance of surviving a zombie encounter differs between zombie killers and non-zombie killers, but if a person doesn't survive the encounter, they become a zombie.

This process can be described by the Modified Zombie Apocalypse equations:

\frac{\partial S}{\partial t} = -BSZ-ESK

\frac{\partial K}{\partial t} = -CKZ+ESK

\frac{\partial Z}{\partial t} = BSZ+CKZ-AKZ

where

    S: number of regular people, who can't kill zombies
    K: number of zombie killers
    Z: number of zombies
    A: rate at which zombies are killed, by K
    B: rate at which regular people are turned into zombies
    C: rate at which zombie killers are turned into zombies
    E: rate at which zombie killers teach regular people how to kill zombies 

(inspired by Munz et al., Infectious Disease Modelling Research Progress, 2009)

Your assignment is to use Boost.Numeric.Odeint or GSL's gsl_odeiv2.h to solve this system of equations. Read these package's documentation for details.

Assuming values

B=0.02, E=0.015, A=0.03, C=0.01, K_0=9

(the latter is the value of K at t=0), your code should determine how many initial zombies, Z0, it takes to turn the whole building population into zombies.

Note that the total number of people in the building is 500, there are K0=9 zombie killers initiallly, so that

S_0=491-Z_0

Also note that you can consider all zombies to be killed if the value of Z goes below 1.

Numerically solve the above set of ODEs for several values of Z0 to determine the value of Z0 above which the zombies win.

Your code should output a netcdf file that contains all three populations (S, K, Z) versus time for at least two values of the initial Z0 values: one in which the zombies win and another one where the zombies lose and all disappear.

There is little opportunity for modularization in this assignment, but we do expect the code to contain a number of functions (i.e., not one monolythic code). We furthermore expect your code to be under git version control (in a separate repository from the previous assignments) with several meaningful commits, and your code to be properly commented.

Submit a text file with the location of your repository and the output of "git log --stat" to the Dropbox by February 28th, 2019 at 11:55 PM.