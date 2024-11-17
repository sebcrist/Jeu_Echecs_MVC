# Projet Final de Développement d'un Jeu d'Échec

Ce projet est un jeu d'échec développé en **C++** en utilisant le framework **Qt**, suivant le modèle de conception **MVC (Modèle-Vue-Contrôleur)**. Il a été réalisé dans le cadre du cours **INF1015**.

---

## Structure du Projet

### Modèle (Model)
Le modèle contient la logique de l'application, y compris les règles du jeu d'échec et l'état actuel du plateau.

- **`ChessBoard.cpp` / `ChessBoard.h`** : Ces fichiers définissent la classe `ChessBoard` qui gère l'état du plateau de jeu, les pièces et les règles du jeu.
- **`Piece.cpp` / `Piece.h`** : Ces fichiers définissent la classe `Piece` et ses sous-classes (comme `King`, `Queen`, etc.) représentant les différentes pièces d'échec et leurs mouvements.

### Vue (View)
La vue est responsable de l'affichage de l'interface utilisateur et de la représentation graphique du plateau de jeu.

- **`MainWindow.cpp` / `MainWindow.h`** : Ces fichiers définissent la classe `MainWindow` qui gère la fenêtre principale de l'application et l'affichage du plateau de jeu.
- **`ChessBoardView.cpp` / `ChessBoardView.h`** : Ces fichiers définissent la classe `ChessBoardView` qui est responsable du rendu graphique du plateau de jeu et des pièces.

### Contrôleur (Controller)
Le contrôleur gère les interactions de l'utilisateur et met à jour le modèle et la vue en conséquence.

- **`GameController.cpp` / `GameController.h`** : Ces fichiers définissent la classe `GameController` qui gère les interactions de l'utilisateur, comme les mouvements des pièces, et met à jour le modèle et la vue.

---

## Autres Fichiers

- **`main.cpp`** : Le point d'entrée de l'application qui initialise le `MainWindow` et lance l'application Qt.

---

