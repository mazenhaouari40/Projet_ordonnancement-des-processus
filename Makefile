CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS =

.PHONY: all clean menu

all:  menu

menu:
	@while true; do \
		echo "Menu:"; \
		echo "1. Compile and run creer_fichier"; \
		echo "2. Compile and run fifo"; \
		echo "3. Compile and run SRT"; \
		echo "4. Compile and run Priorite"; \
		echo "5. Compile and run Round_Robin"; \
		echo "6. Clean"; \
		echo "0. Quit"; \
		read -p "Enter your choice: " choice; \
		case $$choice in \
			1) make run_creer_fichier;; \
			2) make run_fifo;; \
			3) make run_SRT;; \
			4) make run_Priorite;; \
			5) make run_Round_Robin;; \
			6) make clean;; \
			0) exit 0;; \
			*) echo "Invalid choice"; \
			   continue;; \
		esac; \
	done

run_creer_fichier: creer_fichier
	@read -p "Entrez le nombre de processus : " num_processes; \
	read -p "Entrez le temps de début pour date_arrivee : " start_a; \
	read -p "Entrez le temps de fin pour date_arrivee : " end_a; \
	read -p "Entrez le temps de début pour duree_cycle : " start_ex; \
	read -p "Entrez le temps de fin pour duree_cycle : " end_ex; \
	read -p "Entrez le temps de début pour priorite : " start_prio; \
	read -p "Entrez le temps de fin pour priorite : " end_prio; \
	./creer_fichier $$num_processes $$start_a $$end_a $$start_ex $$end_ex $$start_prio $$end_prio

run_fifo: fifo
	./fifo config.txt

run_SRT: SRT
	./SRT config.txt

run_Priorite: Priorite
	./Priorite config.txt

run_Round_Robin: Round_Robin
	@read -p "Entrez la valeur du quantum : " quantum; \
	./Round_Robin config.txt $$quantum

creer_fichier: creer_fichier.o
	$(CC) $(LDFLAGS) $^ -o $@

fifo: fifo.o
	$(CC) $(LDFLAGS) $^ -o $@

SRT: SRT.o
	$(CC) $(LDFLAGS) $^ -o $@

Priorite: Priorite.o
	$(CC) $(LDFLAGS) $^ -o $@

Round_Robin: Round_Robin.o
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f creer_fichier fifo SRT Priorite Round_Robin *.o

