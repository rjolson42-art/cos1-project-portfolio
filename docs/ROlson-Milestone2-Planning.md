> Use this worksheet to plan the next phase of your project **before you begin coding**
> Be clear, specific, and intentional—this will guide your development this week.

---
## 📌 Project Overview

**Project Name:**
→   Portfolio Project
  
**What does your program currently do? (1–3 sentences)**   
→ My program currently runs the main menu loop, builds a battle map, and spawns a unit on the battlefield.

---
## 🔍 Current Progress Check  
  
**What is working right now?**   
→   Currently the battle map and unit spawner are the only things that are working completely.
  
**What is NOT working or incomplete?**   
→   My main menu has issues validating user input which can cause infinite loops or unexpected behavior.
  
**What feels confusing or messy in your code?**   
→ Currently I do not feel that any of my code is messy or confusing.

---
## 🚀 Feature Planning  
  
List the features you plan to add or improve this week.  
  
### Feature 1  
**Name:**   
→    Menu Input Validation
  
**What does this feature do?**   
→   This feature will take the user's input and validate that it is of the correct variable type and compare it to the menu options to help the user make the proper menu selections.
  
**Why is this feature important?**   
→   This feature stops the program from running into issues such as infinite loops or unintended behavior.
  
---
### Feature 2  
**Name:**   
→   Initiative Order Generator and Sorter
  
**What does this feature do?**   
→   This feature will randomly generate initiative for each unit on the battle map and sort them into order based on generated initiative.
  
**Why is this feature important?**   
→   This will dictate the order in which units take turns in the combat simulation.
  
---
  
### Feature 3 (optional)  
**Name:**   
→   Main Battle Loop
  
**What does this feature do?**   
→   This feature dictates the flow of combat allowing each unit to move and attack in their respective initiative order.
  
**Why is this feature important?**   
→   This is the main structure of the simulator that controls most of the program.
  
---
## 🧩 System Design Updates  
  
**Will you need to create any new classes? If so, which ones?**   
→   No
  
**Will you modify any existing classes? How?**   
→   I will need to modify the Unit class by adding a member for initiative, and helper functions to generated and retrieve said member.
I will also need to heavily modify the CombatLogic class by adding in logic to control the combat turns and allow the user to manipulate the units.
  
**What data structures will you use (vectors, 2D vectors, etc.)?**   
→   I will need to add a vector to the CombatLogic class to store active combatants so they can be sorted prebattle and looped During the combat sequence.
  
---
## 🔄 Program Flow  
  
**Describe how a user interacts with your program:**  
  
1. Program starts →   Main menu is displayed allowing the user to choose between starting a battle, looking at instructions, and exiting the program.
2. User chooses →   The user selects one of the menu options.
3. Program responds →   The program takes the user input and runs whichever the user has chosen.
4. Loop/next step →   once the user starts the actual simulation it displays a battle grid with the player's unit spawned onto it. That is currently the end of the steps the user can initiate in the program.
  
---
## 🎯 Usability Improvements  
  
How will you make your program easier to use this week?  
  
- Clearer prompts:   
→   If the user enters an invalid input, the program will prompt the user with why the input was invalid and what the user needs to enter.
  
- Better error handling:   
→   I will be implementing input validation logic to handle errors and exceptions based on the user's input.
  
- Improved menu/navigation:   
→   These changes will provide extra direction for the user while also eliminating possible program breaking errors.
  
---
## 🎯 Usability Improvements  
  
How will you make your program easier to use this week?  
  
- Clearer prompts:   
→   
  
- Better error handling:   
→   
  
- Improved menu/navigation:   
→   
  
---
## ⚠️ Potential Challenges  
  
**What do you think will be the hardest part this week?**   
→   I believe the hardest part of this week for me will be adding the user validation logic.
  
**What is your plan if you get stuck?**   
→   I plan to do a lot of research prior to beginning my code implementation for this so that I can find the most effective way to handle invalid inputs.
  
---
## ⚠️ Potential Challenges  
  
**What do you think will be the hardest part this week?**   
→   
  
**What is your plan if you get stuck?**   
→   
  
---
  
## 📈 Level Up Goal  
  
**What skill are you focusing on improving this week?**   
→   Input Validation
  
**What will you do to improve it?**   
(e.g., tutorial, practice, debugging, office hours)   
→   I plan to research multiple different ways to handle user input and how to effectively mitigate improper input.
  
---
## 🗓️ Task Breakdown (GitHub Issues Planning)  
  
List the tasks you plan to create as GitHub Issues:  
  
- [ ]   Create user input validation logic
- [ ]   Add unit initiative generation and sorting based on initiative
- [ ]   Create a combat loop with distinct phases
- [ ]   
  
---
  
## 🔥 Final Check  
  
Before you start coding, ask yourself:  
  
- [ ] Do I know what I’m building this week?   
- [ ] Do I know where to start?   
- [ ] Did I break my work into small tasks?   
  
If yes → start coding 🚀   
If no → refine your plan first   
  
---
## 😈 Final Thought  
  
> Plan it now… or debug it later.