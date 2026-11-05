// ==========================================
// 1. BEST PRACTICE: Der Header Guard (IMMER standardmäßig nutzen)
// ==========================================
#ifndef SERVER_H
#define SERVER_H

// ==========================================
// 2. INCLUDES: Nur, wenn der Header selbst Datentypen daraus benötigt
// ==========================================
// Beispiel: Wenn ein Funktionsprototyp hier unten "bool" oder "uint32_t" nutzt:
// #include <stdbool.h> 
// #include <stdint.h>
#include <signal.h>

// ==========================================
// 3. DEFINES: Globale Konstanten für das Projekt
// ==========================================
#define PORT 8080
#define MAX_CONNECTIONS 10

extern volatile sig_atomic_t running;

// ==========================================
// 5. FUNKTIONSPROTOTYPEN (Das eigentliche Interface)
// ==========================================
int run_socket();


#endif // SERVER_H (Schließt den Header Guard)
