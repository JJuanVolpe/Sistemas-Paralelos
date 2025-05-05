#!/bin/bash
#SBATCH -N 1
#SBATCH –-exclusive
#SBATCH --partition=Blade
#SBATCH -o directorioSalida/output.txt
#SBATCH -e directorioSalida/errors.txt
./quadratic3OP3
