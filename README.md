# 🦖 Dinorun - A Terminal-Based Dino Game 

Dinorun is a fun and interactive terminal-based game inspired by the classic Dino Run game. It features a charming ASCII art style, customizable characters, and a variety of gameplay options. The game is written in C and designed to run in a terminal environment.

---

## 🎮 Features 

- 👻 **Customizable Characters**: Choose from four different characters, each with unique ASCII art.
- 🌈 **Color Customization**: Personalize the game's color scheme with a variety of options. 
- 🚀 **Dynamic Gameplay**: Experience gravity-based mechanics and avoid obstacles to achieve a high score.
- 🏆 **High Score Tracking**: Save and view your high scores with a simple file-based system. 
- ⌨️ **Interactive Menus**: Navigate through beautifully designed menus using keyboard inputs. 

---

## 🕹️ How to Play 

1. ▶️ **Start the Game**: Launch the game by running the compiled binary. 
2. 🎨 **Main Menu**: Use the keyboard to navigate through the main menu. You can customize your character, change the game speed, and select colors. 
3. **Gameplay**:
   - 🦘 **Jump**: Press `X` to make your character jump and avoid obstacles. 
   - ⏸️ **Pause**: Press `ESC` to pause the game and access the pause menu. 
   - 🏠 **Quit**: Press `M` during the game to return to the main menu. 
4. 📊 **Scores**: Your score is saved automatically. You can view the high scores in the `scores.txt` file. 

---

## 🖥️ Code Structure 

- 🏁 **Main Menu**: Handles the initial setup, character selection, and customization. 
- 🔄 **Game Loop**: Manages the game's logic, including gravity, collision detection, and obstacle spawning. 
- 📝 **Score System**: Reads and writes high scores to a file, allowing for persistent score tracking. 

---

## 📦 Dependencies 

- 📚 **Standard C Libraries**: The game uses standard C libraries like `stdio.h`, `stdlib.h`, and `string.h`. 
- ⏱️ **Termios and Poll**: For non-blocking input handling, the game uses `termios.h` and `poll.h`. 

---

## 🤝 Contributing 

 💡 Contributions are welcome! If you have any ideas for new features, improvements, or bug fixes, feel free to open an issue or submit a pull request. 

---

Enjoy the game and happy running! 🦖🎉
