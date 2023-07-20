#!/bin/bash  
#General syntax for submitting jobs on the KEKCC server.
bsub -q l  basf2 script.py Any_Arguments_Required
#q for queue
#l for jobs up to 24 hours.
#s for jobs taking less than 3 hours
