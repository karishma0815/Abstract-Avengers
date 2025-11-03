# COS 214 Project - Plant Nursery Simulator

![Plant Nursery Simulator](Images/Plant_Nursery_Image.png)

# Contents

- [Description](#description)
- [Documentation and UML diagrams](#documentation)
- [Setup](#setup)
- [Team](#team)

# Description

The Plant Nursery Simulator is a C++ project that models the operations of a lively springtime nursery — from growing plants in the greenhouse to assisting customers on the sales floor.
It uses object-oriented design and software design patterns to manage plant care, customer interactions, and staff coordination.
The goal is to show how structured design brings order and flexibility to a complex, evolving system.

# Documentation

[Report](Documents/Report_Google_Docs.pdf)

[Presentation](Documents/Presentation.pptx)

[UML Diagrams](UML/)

# Setup

### Cloning

```
https://github.com/karishma0815/Abstract-Avengers.git
```

### Building

This project can be built using Makefile:

``` 
Compilation: make (Ensure you are currently in the SystemFiles directory)
Demo Main: make run 
Unit Tests: make test-<test_filename>
```

### Demo Running

When `make run` is executed, you'll be presented with two main options:

#### 1. Interactive Mode (Recommended)
```bash
Choose a mode:
1. DemoMain (Interactive)
2. testingMain

Enter your choice: 1
```

**Interactive Mode Features:**
- **Main Menu**: Navigate between Customer, Staff, Greenhouse, and Pattern Demo sections
- **Customer Experience**: 
  - Browse plants using different iterators (all plants, price range, cart contents)
  - Add/remove items using command pattern
  - Get recommendations using strategy pattern
  - Personalize plants with builder and decorator patterns
  - Complete purchase flow with state pattern
- **Staff Operations**:
  - Plant care commands (water, fertilize, prune, sunlight)
  - Handle plant issues via chain of responsibility
  - Manage inventory through mediator pattern
  - Create staff using factory method pattern
- **Greenhouse Management**:
  - Observe plant lifecycle states
  - Factory production of different plant types
  - Composite plant arrangements

#### 2. Testing Mode (Comprehensive Demo)
```bash
Enter your choice: 2
```

**Automated Testing Demonstrates:**
- All design patterns working together
- Complete customer shopping scenarios
- Staff coordination and plant care workflows
- Inventory management and stock operations
- Plant lifecycle from seedling to sale
- Error handling and edge cases

#### Navigation Tips:
- Use number keys to navigate menus
- Follow on-screen prompts for input validation
- Press Enter to continue after demonstrations
- Each section showcases specific design patterns in action

#### What You'll See:
- **Real-time Pattern Execution**: Watch design patterns solve real nursery problems
- **Interactive Scenarios**: Make choices that affect the simulation
- **Comprehensive Testing**: Automated demos showing all features working together
- **Educational Output**: Clear explanations of which patterns are being used

# Team

<table>
    <tr><th>Member</th><th>Roles</th><th>Avenger</th></tr>
    <tr>
      <td align="center">
        Taskeen Abdoola<br>u22698681<br>
      </td>
      <td align="center">
        The Customers & The Sales Floor: <br>Builder<br>Decorator<br>Adapter<br>State<br>
      </td>
      <td>
        <img src="Images/Scarlet_Witch.jpg" width="200" height="200" style="border-radius: 8px;">
      </td>
    </tr>
    <tr>
      <td align="center">
        Sabira Karie<br>u23591481<br>
      </td>
      <td align="center">
        The Customers & The Sales Floor:
        <br>Command<br>Iterator<br>Strategy<br>
      </td>
      <td>
        <img src="Images/baby-groot-guardians.jpg" width="200" height="200" style="border-radius:8px;">
      </td>
    </tr>
    <tr>
      <td align="center">
        Karishma Boodhoo<br>u23538199<br>
      </td>
      <td align="center">
        The Staff:
        <br>Command<br>Chain of Responsibility<br>Mediator<br>Factory Method<br>
      </td>
      <td>
        <img src="Images/Captain_Marvel.jpg" width="150" height="200" style="border-radius: 8px;">
      </td>
    </tr>
    <tr>
      <td align="center">
        Rene Reddy<br>u23558572<br>
      </td>
      <td align="center">
        Greenhouse/Garden Area:
        <br>State<br>
      </td>
      <td>
        <img src="Images/Black_Widow.jpg" width="200" height="200" style="border-radius: 8px;">
      </td>
    </tr>
    <tr>
      <td align="center">
        Kiolin Gounden<br>u22647300<br>
      </td>
      <td align="center">
        Greenhouse/Garden Area:
        <br>Factory Method<br>Observer<br>Composite<br>
      </td>
      <td>
        <img src="Images/Batman.jpg" width="200" height="200" style="border-radius: 8px;">
      </td>
    </tr>
</table>
