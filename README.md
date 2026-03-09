_This project has been created as part of the 42 curriculum by mfunakos, yohatana, keishii, kmoriyam._

# Oekaki Island (お絵描きアイランド)

## Description

**Oekaki Island** (お絵描きアイランド) is a real-time online drawing guessing game built as the final project of the 42 Common Core curriculum. Players create or join game rooms, take turns drawing prompts while others guess the word, and compete for high scores.

### Key Features

- **Authentication**: Email/password registration and login, Google OAuth
- **Game Rooms**: Create rooms with invitation tokens, support for players and spectators
- **Game Modes**: DEFAULT mode and ONE_STROKE mode (single-stroke drawing challenge)
- **Real-time Gameplay**: WebSocket-based drawing canvas, chat, timer, and scoreboard
- **User Profiles**: Avatar, badges, total score, ranking, and play statistics
- **Legal Pages**: Terms of Service and Privacy Policy

---

## Instructions

### Prerequisites

- **Docker** and **Docker Compose** (recommended for running the full stack)
- **Node.js 18+** (optional, for local development without Docker)

### Environment Setup

1. Copy the example environment file:

    ```bash
    cp .env.example .env
    ```

2. Edit `.env` and configure the following variables:
    - `DATABASE_URL` – PostgreSQL connection string (default: `postgresql://oekaki:password@localhost:5432/oekaki_db`)
    - `JWT_SECRET` – Secret key for JWT signing (change in production)
    - For Google OAuth: `GOOGLE_CLIENT_ID`, `GOOGLE_CLIENT_SECRET`
    - `NGROK_AUTHTOKEN` – For `make ngrok` (optional)

### Running the Project

1. Start all services **with ngrok** (for demos / remote play):

    ```bash
    make up
    ```

    This runs `docker compose --profile ngrok up -d`, seeds the DB, and then prints the ngrok URL.

2. Or start services **without ngrok** (local development only):

    ```bash
    make local
    ```

3. Access the application:
    - **App (localhost)**: http://localhost:5173
    - **App (ngrok)**: URL printed after `make up` (you can also run `make url-ngrok`)
    - **Database**: localhost:5432 (PostgreSQL)

4. **Google OAuth**: Register these redirect URIs in Google Cloud Console:
    - `http://localhost:3000/v1/auth/google/callback` (when logging in from localhost:5173)
    - `https://xxx.ngrok-free.dev/v1/auth/google/callback` (when using ngrok)

### Local Development (without Docker)

1. Start PostgreSQL (or use Docker for the database only)
2. Run migrations:
    ```bash
    cd backend && npx prisma migrate dev
    ```
3. Seed the database (optional):
    ```bash
    cd backend && npx prisma db seed
    ```
4. Start the backend:
    ```bash
    cd backend && npm run dev
    ```
5. Start the frontend:
    ```bash
    cd frontend && npm run dev
    ```

---

## Resources

### Documentation & References

- [React Documentation](https://react.dev/)
- [Vite Documentation](https://vitejs.dev/)
- [Fastify Documentation](https://fastify.dev/)
- [Prisma Documentation](https://www.prisma.io/docs)
- [WebSocket API (MDN)](https://developer.mozilla.org/en-US/docs/Web/API/WebSocket)
- [Tailwind CSS](https://tailwindcss.com/)
- [DaisyUI](https://daisyui.com/)

### AI Usage

AI was used in the following areas:

- **Database schema**: Assistance with table definitions, relationships, and migrations.
- **Reference materials**: Translation of documentation and external resources.
- **UI design**: Support for layout decisions, component structure, and styling.
- **Code review**: Feedback on implementation and suggestions for improvements.
- **Debugging**: Help identifying and resolving bugs and errors.

---

## Team Information

| Member   | Assigned Role(s)     | Responsibilities                          |
| -------- | -------------------- | ----------------------------------------- |
| mfunakos | PM, Developer        | Project progress, progress management     |
| yohatana | PO, Developer        | Overall coordination, decision-making     |
| keishii  | Tech Lead, Developer | Technology selection, development support |
| kmoriyam | Tech Lead, Developer | Technology selection, development support |

---

## Project Management

### Work Organization

- **Task distribution**: Each member implemented both frontend and backend for their assigned features. Tasks were managed using GitHub Issues integrated with GitHub Projects, where each member created issues for their own tasks. Typically, one PR corresponded to one issue.
- **Development workflow**: Pull requests required passing CI checks (frontend/backend builds and formatting via GitHub Actions). Reviews by one or two team members were mandatory before merging. A PR template was used to document the summary, changes, testing steps, and review points.
- **Meetings**: Team members worked together at the campus daily, enabling continuous in-person communication. Formal meetings were held as needed rather than on a fixed schedule.
- **Source code management**: Git and GitHub. Branch naming convention: `<issue-number>-<feat|fix>-</description>`(e.g, `42-feat/game_mode`). Direct pushes to main were prohibited.

### Tools

- **Project Management**: GitHub Issues + GitHub Projects (task tracking), GitHub Actions (CI)
- **Documentation**: Notion (requirements, game rules, project structure, task overview)
- **Design**: Figma (UI / visual prototyping)
- **Version Control**: Git, GitHub

### Communication

- **Channels**: Discord, in-person at campus

---

## Technical Stack

### Frontend

| Technology   | Version | Purpose                   |
| ------------ | ------- | ------------------------- |
| React        | 19      | UI framework              |
| Vite         | 7       | Build tool and dev server |
| TypeScript   | 5.9     | Type safety               |
| React Router | 7       | Client-side routing       |
| Tailwind CSS | 4       | Utility-first CSS         |
| DaisyUI      | -       | Component library         |

**Justification**: The team chose modern, widely-used technologies for frontend development. React was selected as a poplular and well-surpported UI framework. TypeScript adds type safety over plain JavaScript, reducing bugs. Vite provides fast builds and hot module replacement for a smooth development experience. Tailwind CSS and Daisy UI were chosen for rapid styling, with Daisy UI offering ready-made components that integrate well with React.

### Backend

| Technology         | Version | Purpose                       |
| ------------------ | ------- | ----------------------------- |
| Fastify            | 5       | Web framework                 |
| Prisma             | 6       | ORM and database toolkit      |
| TypeScript         | 5.9     | Type safety                   |
| Zod                | -       | Schema validation             |
| @fastify/websocket | -       | WebSocket support             |
| bcrypt             | -       | Password hashing              |
| JWT                | -       | Session/authentication tokens |

**Justification**: Fastify was chosen for its high performance, which is important for real-time game features like drawing and chat over WebSocket. Prisma provides a type-safe and convenient way to interact with the database, with built-in migration support. Zod handles request validation, bcrypt secures password hashing, and JWT manages user authentication - these were adopted as standard tools for building a secure backend.

### Database

- **PostgreSQL 16** (Alpine image in Docker)

**Justification**: PostgreSQL was chosen as a modern and reliable relational database. The project requires complex relationShips between users, rooms, rounds, and badges, which fit well with a relational model. It also integrates smoothly with Prisma ORM.

### Infrastructure

| Technology              | Purpose                                           |
| ----------------------- | ------------------------------------------------- |
| Docker / Docker Compose | Containerization and service orchastration        |
| Make                    | Build automation and command shortcuts            |
| ngrok                   | HTTPS tunneling for OAuth testing and remote play |

**Justification**: Docker and Docker Compose are used to containerize and orchestrate the frontend, backend, and database services. Make simplifies common operations (build, start, seed) into sigle commands. ngrok provides HTTPS tunneling, which is needed for Google OAuth and for remote play over the network.

---

## Database Schema

### Entity Relationship Diagram

```mermaid
erDiagram
    User ||--o{ Session : has
    User ||--o{ UserAuthentication : has
    User ||--o{ UserBadge : has
    Badge ||--o{ UserBadge : has
    User ||--o{ Room : hosts
    Room ||--o{ Round : contains
    Room ||--o{ RoomMember : has
    User ||--o{ RoomMember : joins
    User ||--o{ Round : draws
    User ||--o{ Round : wins
```

### Tables and Relationships

| Table                  | Description                             | Key Fields (with types)                                                                                                                       |
| ---------------------- | --------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------- |
| **User**               | User accounts and profile data          | id (Int), name (String), email (String), password (String?), avatar (String), total_score (Int?), first_place_count (Int?), play_count (Int?) |
| **Session**            | User sessions (JWT/session management)  | id (String), user_id (Int), expires_at (DateTime)                                                                                             |
| **UserAuthentication** | OAuth provider links (e.g. Google)      | user_id (Int), provider (String), provider_user_id (String)                                                                                   |
| **Badge**              | Achievement badges                      | id (Int), name (String?), description (String?)                                                                                               |
| **UserBadge**          | Many-to-many: users and badges          | user_id (Int), badge_id (Int), createdAt (DateTime)                                                                                           |
| **Room**               | Game rooms                              | id (Int), host_id (Int), game_mode (GameMode), invitation_token (String?), status (RoomStatus)                                                |
| **Round**              | Individual drawing rounds within a room | id (Int), room_id (Int), drawer_id (Int), word (String?), winner_id (Int?), duration (Int)                                                    |
| **RoomMember**         | Users in a room (players or spectators) | room_id (Int), user_id (Int), is_ready (Boolean), role (UserRole), score (Int)                                                                |

### Enums

- **GameMode**: `DEFAULT`, `ONE_STROKE`
- **RoomStatus**: `WAITING`, `PLAYING`, `RESULT`, `FINISHED`
- **UserRole**: `PLAYER`, `SPECTATOR`

---

## Features List

| Feature                           | Team Member(s) | Description                                                    |
| --------------------------------- | -------------- | -------------------------------------------------------------- |
| Email/Password Authentication     | mfunakos       | Registration, login                                            |
| Google OAuth                      | mfunakos       | Login and register with Google account                         |
| Room Creation & Invitation        | kmoriyam       | Create rooms, generate invitation tokens, join via link        |
| Game Modes (DEFAULT, ONE_STROKE)  | keishii        | Two play modes: standard drawing and single-stroke challenge   |
| Real-time Drawing & Chat          | keishii        | WebSocket-based canvas, chat messages, timer, scoreboard       |
| Profile, Ranking & Badges         | yohatana       | User profile, avatar, badges, total score, play count, ranking |
| Terms of Service & Privacy Policy | yohatana       | Static legal pages                                             |

---

## Modules

### Module Summary

**Total: 15 points** (5 Major × 2pts + 5 Minor × 1pt)

| Module Name                                                                                   | Type (Major/Minor) | Points | Justification                                                                                           | Implemented By    |
| --------------------------------------------------------------------------------------------- | ------------------ | ------ | ------------------------------------------------------------------------------------------------------- | ----------------- |
| Use a framework for both the frontend and backend.                                            | Major              | 2      | React + Vite (frontend) and Fastify (backend) provide structure, maintainability, and fast development. | All               |
| Implement real-time features using WebSockets or similar technology.                          | Major              | 2      | Drawing canvas, chat, timer, and scoreboard sync in real time via WebSocket.                            | keishii           |
| Implement a complete web-based game where users can play against each other.                  | Major              | 2      | Oekaki Island: drawing guessing game where users take turns drawing and guessing.                       | keishii           |
| Remote players — Enable two players on separate computers to play the same game in real-time. | Major              | 2      | Users join rooms via invitation tokens and play together over WebSocket.                                | kmoriyam, keishii |
| Multiplayer game (more than two players).                                                     | Major              | 2      | Multiple players join a room; RoomMember supports several players per game.                             | kmoriyam          |
| Implement remote authentication with OAuth 2.0 (Google, GitHub, 42, etc.).                    | Minor              | 1      | Google OAuth for sign-in and registration.                                                              | mfunakos          |
| Implement spectator mode for games.                                                           | Minor              | 1      | UserRole SPECTATOR lets users watch games without playing.                                              | kmoriyam          |
| Game customization options.                                                                   | Minor              | 1      | DEFAULT and ONE_STROKE modes; room host selects game mode.                                              | kmoriyam, keishii |
| Use an ORM for the database.                                                                  | Minor              | 1      | Prisma for type-safe queries, migrations, and schema management.                                        | All               |
| A gamification system to reward users for their actions.                                      | Minor              | 1      | Badges, total score, ranking, and play statistics.                                                      | yohatana          |

### Implementation Overview

- **Framework (frontend/backend)**: React with Vite for the SPA; Fastify for the REST API. Shared TypeScript across both.
- **WebSocket**: `@fastify/websocket` on the backend. `connectionHandler` broadcasts draw, chat, timer, and round events. `chatHandler` validates guesses and updates scores.
- **Complete game**: Round lifecycle (ROUND_START → draw/guess → ROUND_END → RESULT). `wordSelector` picks prompts; correct answers update scores and advance the round.
- **Remote players**: Users join via invitation links (`/rooms/join` with token). WebSocket keeps all clients in sync regardless of location.
- **Multiplayer**: `RoomMember` stores players per room. `MAX_MEMBERS` caps room size. Multiple players compete in each round.
- **OAuth 2.0**: Google OAuth flow with redirect and callback. `UserAuthentication` links provider accounts. State in httpOnly cookie for CSRF protection.
- **Spectator mode**: `UserRole.SPECTATOR` in `RoomMember`. Host toggles roles in Waiting. Spectators receive game events but cannot chat or draw.
- **Game customization**: `GameMode` enum (DEFAULT, ONE_STROKE). Host updates via `PATCH /rooms/:id/game-mode`. ONE_STROKE restricts the drawer to a single stroke per turn.
- **ORM**: Prisma for all DB access. Migrations for schema changes. Type-safe client generated from schema.
- **Gamification**: `Badge` and `UserBadge` models. `total_score`, `play_count`, `first_place_count` on User. Profile API returns ranking and top players.

---

## Individual Contributions

### mfunakos

**Role**: PM, Developer — Project progress, progress management

**Features & Modules Implemented**:

- **Email/Password Authentication**: Implemented registration (`POST /register`) and login (`POST /login`) with bcrypt password hashing. Zod validation for request bodies. Duplicate email/name checks on registration. Auto-login after successful registration via session creation and cookie. Frontend: `AccountRegister.tsx`, `Login.tsx`, `authApi.ts`, `AuthProvider`, `RequireAuth`, `RequireGuest`.

- **Google OAuth**: Implemented OAuth 2.0 flow with Google. Backend: `googleAuth` (redirect to Google), `googleCallback` (exchange code for user info), `handleGoogleLogin`, `handleGoogleRegister`. State stored in httpOnly cookie for CSRF protection. Handles existing users (email conflict, account not found). `UserAuthentication` model links OAuth providers. Frontend: `GoogleAccountLogin`, `GoogleAccountRegister`, `RedirectLogin`, `SetupProfile` (post-OAuth profile setup).

**Challenges & Solutions**:

- **OAuth state validation**: Used httpOnly cookie to store OAuth state (nonce + mode) to prevent CSRF; validated state on callback and cleared after use.
- **Origin validation**: `isAllowedOrigin` restricts OAuth redirect URIs to configured frontend origins (localhost, ngrok).

### yohatana

**Role**: PO, Developer — Overall coordination, decision-making

**Features & Modules Implemented**:

- **Profile, Ranking & Badges**: Implemented profile API (`GET /profile`) returning user name, avatar, total_score, first_place_count, play_count, badges, user_rank, and top_ranker (leaderboard). Backend: `userController.getProfile`, Badge/UserBadge models. Frontend: `Profile.tsx` (profile page with stats, badges grid, leaderboard), `BadgeImage` component, `userApi`, `profileData` types.

- **Terms of Service & Privacy Policy**: Implemented static legal pages. Frontend: `TermsOfService.tsx`, `PrivacyPolicy.tsx`, `TermsOfServiceContent`, `PrivacyPolicyContent`, routes `/terms` and `/privacy-policy`. Footer links to both pages.

- **Gamification System**: Badge model and UserBadge many-to-many relation. Badges seeded (e.g. first win, happy player, rich score). Profile displays earned badges. Score and play statistics updated in `roomManager.finalizeGame` (integrated with game flow). Ranking computed by `total_score` DESC.

**Challenges & Solutions**:

- **Ranking calculation**: Used `prisma.user.count` with `where: { total_score: { gt: user.total_score } }` to compute user rank without loading all users.

### keishii

**Role**: Tech Lead, Developer — Technology selection, development support

**Features & Modules Implemented**:

- **Game Screen**: Built the main game screen with role-based UI. The drawer can draw on the canvas with pen color selection, eraser, canvas clear, and word skip. Guesser cannot see the word or use drawing tools, and their chat messages are checked for correct answers. Spectators can only watch - drawing and chat are both disabled. Shared components include the timer and scoreboard.

- **Game Flow**: Managed the round lifecycle. On `ROUND_START`, a word is selected and the timer begins. When the timer ends, scores are saved to the DB and players return to the Prepare screen for the next round. After all rounds finish, badge-related data is updated and the game moves to the Result screen. Also implemented reconnection handling - when a player joins via invite URL, they are redirected to the correct screen based on the current game state.

- **Real-time Drawing & Chat**: WebSocket-based architecture. Backend: `connectionHandler` (JOIN, DRAW, DRAW_END, CLEAR, CHAT, ROUND_START, ROUND_END, TIMER), `chatHandler` (correct-answer detection, score updates, word replacement), `timerManager` (per-room countdown), `roomManager` (broadcast, scores, round state). Frontend: `wsClient`, `Game.tsx` (WebSocket connect, message handling), `Canvas.tsx` (draw events over WebSocket), `ChatMessages`, `ChatInput`, `Timer`, `ScoreBoard`.

- **`ONE_STROKE` Mode**:Implemented as an alternative game mode where the drawer can only draw a single continuous line. If the drawer starts a new stroke, the previous one is automatically cleared from the canvas.

- **Result Screen**: Displays final scores with players sorted by ranking. Players can choose to return to the home screen or start a rematch by creating a new room.

**Challenges & Solutions**:

- **Frontend vs Backend responsibility**: Decided to handle most game logic on the backend to prevent cheating. For example, the timer runs server-side to prevent tampering, and WebSocket messages are filtered by role - the word is sent to the drawer but hidden from guessers.
- **WebSocket reconnection**: Faced an infinite loop where the connection would repeatedly connect, disconnect, and reconnect. Resolved by following React's recommended practice of using cleanup functions in useEffect to properly stop and undo the effect, which prevented duplicate connections.

### kmoriyam

**Role**: Tech Lead, Developer — Technology selection, development support

**Features & Modules Implemented**:

- **Room Creation & Invitation**: Implemented room creation API (`POST /rooms`) with UUID-based invitation tokens. Users can create rooms from the Home page and share invitation links. The `joinRoomByToken` endpoint (`POST /rooms/join`) validates tokens, handles duplicate joins (reload-safe), and enforces room capacity (`MAX_MEMBERS`). Frontend: `roomApi`, `Home.tsx` (create room), `Waiting.tsx` (copy invitation URL to clipboard).

- **Spectator Mode**: Added `UserRole` enum (`PLAYER`, `SPECTATOR`) to the schema and `updateRoomMemberRole` API. Hosts can toggle members between player and spectator in the Waiting room. Spectators can watch games in real time but cannot send chat messages (enforced in `chatHandler.ts`). Frontend: role toggle in `Waiting.tsx`, spectator count in `Prepare.tsx`, `isSpectator` handling in `Game.tsx`.

- **Game Customization Options**: Implemented `GameMode` enum (`DEFAULT`, `ONE_STROKE`) and `updateGameMode` API. Hosts can select the game mode before starting the game. Changes are broadcast to the room via WebSocket. Frontend: game mode selection UI in `Waiting.tsx` (host-only).

**Challenges & Solutions**:

- **Player limit when switching roles**: When a spectator switches to player, the backend checks if the room has reached `MAX_MEMBERS` and returns an error to prevent overcapacity.
- **Invitation token uniqueness**: Migration added a unique constraint on `invitation_token` to avoid collisions.

---

## Additional Information

### Known Limitations

- **Password reset**: Currently not fully implemented.
- **Game effects**: No animations or sound effects to enhance the gameplay experience.
- **Mobile support**: The UI is not fully optimized for smartphone screens.
- **Word generation**: Words are loaded from a static file rather than generated dynamically.
- **Answer matching**: Only hiragana input is accepted for guessing - katakana or kanji answers are not supported.
- **Console error interpretation**: The team concluded that the "no errors in browser console" requirement refers to browser-generated errors, not application-level messages intentionally logged by the code.
