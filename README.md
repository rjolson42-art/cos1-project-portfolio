# 🚀 Welcome to Project & Portfolio!

This repository will be used to keep track of research and development conducted in this class. Follow the instructions below to get started.
cos
### Getting Started

**1.** Review the [About](./docs/01_about/README.md) README and all of the links it provides.

**2.** Review the documentation and [Getting Started](./docs/02_getting_started/README.md) steps in this repository's docs folder.

**3.** Attend the first Live Lecture to see a live setup demo. If you are unable to attend, make sure to watch the archive.

### Next Steps...

After completing the above steps, feel free to begin updating this readme where indicated below. Remember to update this document each week to receive proper credit for the weekly Milestone assignment.

<br>

> ❗️ &nbsp; Now that you have read to this point, go ahead and delete this sentence and everything above it.

<br>

# Project & Portfolio 1

### Student First & Last Name

Hello my name is Russell Olson. I am a student from Minnesota. The purpose of this repository is to practice development using version control. This work will help me begin to build a portfolio of skills and accomplishment that can be shared in the future.

<br>

## 📢 &nbsp; Weekly Stand Up

Each week I will summarize my milestone activity and progress by writing a stand-up. A stand-up is meant to be a succinct update on how things are going. Use these prompts as a guide on what to write about:

⚙️ Overview - What I worked on this past week
<br>
🌵 Challenges - What problems did I have & how I'm addressing them
<br>
🏆 Accomplishments - What is something I "leveled up" on this week
<br>
🔮 Next Steps - What I plan to prioritize and do next

<br>

### Week 1

This week I focused on building the core architecture for my combat simulator. I implemented my foundational classes to handle the 2D grid rendering and object management as well as got a small head start on the combat logic portion of my project. The biggest challenge that I had to work through this week was time management. I came in to the course a bit behind the eight ball this week, but a few late nights and cancelled plans goes a long way to help get caught up. I also had a little trouble with directory paths this week as I had not had separate folders for my source and implementation files before. This was a good learning experience for me about how to code directory paths differently. My biggest accomplishment this week was implementing my dynamic battle grid system as i had not worked with 2D vectors before. Next week I plan to build out the combat loop for my simulator and depending on how long that takes, possibly expand on player and enemy stats or add items to the simulator.  

### Week 2

This week I focused on building out the core groundwork for my tactical grid combat simulator. I organized my task roadmap in GitHub Issues, got the main menu operational, and laid out the initial battlefield grid display. My main hurdle this week was anticipating edge cases with user menu choices and avoiding state corruption when bad inputs hit standard input. Working through input stream error handling took extra time to ensure invalid options don't break the main simulation loop. I successfully implemented basic input validation loops for the main menu, clear error prompts for invalid entries, and laid out the underlying data structure for the combat grid and turn phase tracking. Heading into week 3, my main focus will be fleshing out the combat itself and adding in AI action logic to enemy combatants.

### Week 3

This week I focused on setting up my GitHub Issues for Milestone 3 and planning out key refactoring goals for the tactical grid combat simulator, including grid resizing and enemy AI logic.

Challenges

My biggest hurdle this week was working around console window limitations. Adjusting the combat grid so it displays cleanly without awkward line wrapping required tuning the grid layout and handling boundary checks carefully.

Accomplishments

I successfully mapped out my upcoming task milestones in GitHub Issues and finalized the layout logic for dynamic grid sizing to ensure the battlefield fits properly in the console.

Next Steps

Heading into next week, my main focus will be implementing the enemy AI class logic to control enemy units, allowing them to calculate movement paths and engage in combat turns automatically.
### Week 4

This final week focused on bringing the C++ tactical grid combat simulator to completion, finalizing the combat loop, and conducting comprehensive testing across all menu systems and unit behaviors. Project Wrap-Up I fully implemented the enemy unit AI logic to handle movement path calculations and automated attacks, cleaned up grid rendering for consistent console display, and polished user input validation to prevent menu crashes. Challenges The main challenge was managing state and boundary checks within the tactical grid to prevent out-of-bounds movement and memory corruption during enemy AI turns. I worked through this by stepping through unit movement vectors and validating grid constraints prior to updating positions. Biggest Takeaway My biggest takeaway from this course has been the importance of upfront architectural planning and modular class design. Breaking features into small, isolated classes and mapping tasks into GitHub Issues made complex logic like turn management and grid state far easier to implement and debug. Future Development If I continued developing this project beyond this course, I would add a persistent save/load system using file I/O to store player progress and introduce diverse terrain tile types with unique movement penalties.
