# Gestion d'un personnel universitaire

Exercice 3 – Programmation orientée objet en C++
UNSTIM – Licence 3 Mathématiques et Informatique

## Description

Modélisation d'un personnel universitaire (enseignants, agents administratifs, techniciens) en C++.
Le projet illustre : **héritage**, **classe abstraite**, **méthodes virtuelles**, **redéfinition (`override`)**, **polymorphisme** et **liaison dynamique**.

## Membres du groupe

- ONIFADE Adio
- DANDJINOU Alida
- CAPO-CHICHI Luce
- BANKOLE Grace
- KINIFFO Mistourath
- BOURANDI Worou Alassane
- BANKOLE Grace
- PADONOU Socrates

## Hiérarchie des classes

- `Employe` (classe **abstraite**) : matricule, nom, prénom, salaire de base
  - `Enseignant` : heures supplémentaires + indemnité de recherche
  - `AgentAdministratif` : prime de rendement + prime de responsabilité
  - `Technicien` : prime de risque + prime d'astreinte

La méthode `calculerSalaire()` est **virtuelle pure** dans `Employe` et redéfinie dans chaque classe dérivée.

## Compilation et exécution

Prérequis : un compilateur C++ supportant C++17 (g++ 7 ou plus).

```bash
cd src
g++ -std=c++17 -Wall -Wextra -o personnel main.cpp
./personnel
```

Sous Windows : `personnel.exe`.

### Sans rien installer (GitHub Codespaces)

1. Sur la page du dépôt, cliquer sur **Code** puis **Codespaces** puis **Create codespace**.
2. Dans le terminal, lancer les commandes ci-dessus.

## Résultat attendu

Le programme affiche les informations de 6 employés (2 enseignants, 2 agents administratifs, 2 techniciens), le salaire calculé de chacun, puis le nombre d'employés et la masse salariale totale (2 717 000 FCFA).

## Remarques

- Les données (noms, montants en FCFA) sont des valeurs de test.
- Les formules de salaire sont des hypothèses de modélisation, détaillées dans le rapport.
