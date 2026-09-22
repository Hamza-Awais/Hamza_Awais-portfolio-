# Friend Recommendation System

| **Course** | Data Structures (DS) |
| **Language** | C++ |
| **Type** | Console application |

A social network friend suggestion engine built entirely from scratch with native C++ data structures. Users and their friendships form a graph stored in a hand-written HashMap of linked lists, candidate friends are discovered with a breadth-first search, and suggestions are ranked by a score that combines mutual friends, shared interests and network distance. The whole project is delivered as a single source file.

## Features
- **Custom containers only:** DynamicArray, singly LinkedList, circular-array Queue and a separate-chaining HashMap are all implemented from scratch, no STL containers for the core logic
- **Friendship graph:** users are nodes and friendships are undirected edges held in a HashMap adjacency list
- **Breadth-first search:** finds candidate friends up to distance 3 (friends of friends of friends)
- **Recommendation scoring:** ranks every candidate by mutual friends, shared interests, interest similarity (Jaccard) and network distance
- **Register user:** add a new user with a comma-separated interest list
- **Add / remove friendship:** link or unlink two users with validation against self-friending and duplicates
- **View friends & mutual friends:** list a user's friends and the mutual friends between any two users
- **Search by name:** case-insensitive partial-name lookup across all users
- **File handling:** load users and friendships from `users.txt` / `friends.txt` and save them back
- **Safe input:** non-numeric choices and unknown IDs are rejected without crashing or looping forever

## How it works
- **HashMap** gives O(1) average lookup for users and for each user's adjacency list of friend IDs.
- **LinkedList** stores every adjacency list and every traversal result; **Queue** drives the breadth-first search layer by layer.
- **BFS** from the target user collects all reachable users within distance 3, tagging each with its shortest distance.
- **Scoring:** `mutualFriends * 10 + sharedInterests * 7 + interestSimilarity * 20`, plus a distance bonus of `15` for distance 2 and `8` for distance 3. Candidates are then sorted by score descending and the top K are shown.
- **DynamicArray** holds the candidate profiles and the final ranked recommendations.

## Files
- `friend_recommendation_system.cpp`: the complete source code (all classes and `main` in one file)
- `Friend_Recommendation_System_Documentation.docx`: full project documentation
- `users.txt`: sample user records (id, name, interests)
- `friends.txt`: sample friendship pairs

