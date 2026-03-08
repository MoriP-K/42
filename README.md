_This project has been created as part of the 42 curriculum by mfunakos, yohatana, keishii, kmoriyam._

# Oekaki Island (お絵描きアイランド)

## Description

**Oekaki Island** (お絵描きアイランド) is a real-time online drawing guessing game built as the final project of the 42 Common Core curriculum. Players create or join game rooms, take turns drawing prompts while others guess the word, and compete for high scores.

### Key Features

- **Authentication**: Email/password registration and login, Google OAuth, password reset via email
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

1. Start all services:

    ```bash
    make up
    ```

2. Access the application:
    - **localhost**: http://localhost:5173
    - **ngrok** (after `make ngrok`): https://xxx.ngrok-free.dev
    - **Database**: localhost:5432 (PostgreSQL)

3. **Google OAuth**: Register these redirect URIs in Google Cloud Console:
    - `http://localhost:3000/v1/auth/google/callback`（localhost:5173 からログイン時）
    - `https://xxx.ngrok-free.dev/v1/auth/google/callback`（ngrok 経由時）

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

[TODO: Describe how AI was used in this project. Specify which tasks and which parts of the project involved AI assistance (e.g., code generation, debugging, documentation, architecture decisions). Be specific and honest.]

---

## Team Information

| Member   | Assigned Role(s)     | Responsibilities             |
| -------- | -------------------- | ---------------------------- |
| mfunakos | PM, Developer        | プロジェクトの進行、進捗管理 |
| yohatana | PO, Developer        | 全体統括、意思決定           |
| keishii  | Tech Lead, Developer | 技術選定、開発支援           |
| kmoriyam | Tech Lead, Developer | 技術選定、開発支援           |

---

## Project Management

### Work Organization

[TODO: Describe how the team organized the work: task distribution, meeting schedule, sprint structure, etc.]
タスクの振り分け：ウェブアプリケーションのページごとに各メンバーがフロントエンドとバックエンドを実装
ミーティング：Discordで連絡を取りつつ、必要な時に校舎で実施
ソースコード管理：GitHubでソースコードの管理、レビューを行った

### Tools

- **Project Management**: GitHub Issues, Notion
- **Version Control**: Git, GitHub

### Communication

- **Channels**: Discord

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

**Justification**: React and Vite provide a modern SPA experience with fast development and builds. TypeScript ensures type safety across the frontend. Tailwind and DaisyUI enable rapid, consistent UI development.

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

**Justification**: Fastify offers high performance and a plugin-based architecture. Prisma provides type-safe database access and migrations. WebSocket support enables real-time game and chat features.

### Database

- **PostgreSQL 16** (Alpine image in Docker)

**Justification**: PostgreSQL was chosen for its robustness, support for relational data (users, rooms, rounds, sessions), and excellent Prisma integration. The schema requires complex relationships (users, rooms, rounds, badges) that fit well with a relational model.

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

| Table                  | Description                             | Key Fields                                                                    |
| ---------------------- | --------------------------------------- | ----------------------------------------------------------------------------- |
| **User**               | User accounts and profile data          | id, name, email, password, avatar, total_score, first_place_count, play_count |
| **Session**            | User sessions (JWT/session management)  | id, user_id, expires_at                                                       |
| **UserAuthentication** | OAuth provider links (e.g. Google)      | user_id, provider, provider_user_id                                           |
| **Badge**              | Achievement badges                      | id, name, description                                                         |
| **UserBadge**          | Many-to-many: users and badges          | user_id, badge_id                                                             |
| **Room**               | Game rooms                              | id, host_id, game_mode, invitation_token, status                              |
| **Round**              | Individual drawing rounds within a room | id, room_id, drawer_id, word, winner_id, duration                             |
| **RoomMember**         | Users in a room (players or spectators) | room_id, user_id, is_ready, role, score                                       |

### Enums

- **GameMode**: `DEFAULT`, `ONE_STROKE`
- **RoomStatus**: `WAITING`, `PLAYING`, `RESULT`, `FINISHED`
- **UserRole**: `PLAYER`, `SPECTATOR`

---

## Features List

| Feature                           | Team Member(s) | Description                                                    |
| --------------------------------- | -------------- | -------------------------------------------------------------- |
| Email/Password Authentication     | mfunakos       | Registration, login, password reset via email                  |
| Google OAuth                      | mfunakos       | Login and register with Google account                         |
| Room Creation & Invitation        | kmoriyam       | Create rooms, generate invitation tokens, join via link        |
| Game Modes (DEFAULT, ONE_STROKE)  | keishii        | Two play modes: standard drawing and single-stroke challenge   |
| Real-time Drawing & Chat          | keishii        | WebSocket-based canvas, chat messages, timer, scoreboard       |
| Profile, Ranking & Badges         | yohatana       | User profile, avatar, badges, total score, play count, ranking |
| Terms of Service & Privacy Policy | yohatana       | Static legal pages                                             |

---

## Modules

[TODO: List all chosen modules (Major and Minor) from the 42 ft_transcendence subject. Include point calculation (Major = 2pts, Minor = 1pt), justification for each module choice, implementation overview, and which team member(s) worked on each module.]

### Module Summary Template

| Module Name                                                                                   | Type (Major/Minor) | Points | Justification                                                                                           | Implemented By |
| --------------------------------------------------------------------------------------------- | ------------------ | ------ | ------------------------------------------------------------------------------------------------------- | -------------- |
| Use a framework for both the frontend and backend.                                            | Major              | 2      | React + Vite (frontend) and Fastify (backend) provide structure, maintainability, and fast development. | All            |
| Implement real-time features using WebSockets or similar technology.                          | Major              | 2      | Drawing canvas, chat, timer, and scoreboard sync in real time via WebSocket.                            | keishii        |
| Implement a complete web-based game where users can play against each other.                  | Major              | 2      | Oekaki Island: drawing guessing game where users take turns drawing and guessing.                       | keishii        |
| Remote players — Enable two players on separate computers to play the same game in real-time. | Major              | 2      | Users join rooms via invitation tokens and play together over WebSocket.                                | keishii        |
| Multiplayer game (more than two players).                                                     | Major              | 2      | Multiple players join a room; RoomMember supports several players per game.                             | keishii        |
| Implement remote authentication with OAuth 2.0 (Google, GitHub, 42, etc.).                    | Minor              | 1      | Google OAuth for sign-in and registration.                                                              | mfunakos       |
| Implement spectator mode for games.                                                           | Minor              | 1      | UserRole SPECTATOR lets users watch games without playing.                                              | kmoriyam       |
| Game customization options.                                                                   | Minor              | 1      | DEFAULT and ONE_STROKE modes; room host selects game mode.                                              | kmoriyam       |
| Use an ORM for the database.                                                                  | Minor              | 1      | Prisma for type-safe queries, migrations, and schema management.                                        | All            |
| A gamification system to reward users for their actions.                                      | Minor              | 1      | Badges, total score, ranking, and play statistics.                                                      | yohatana       |

_Note: This project implements a drawing guessing game (お絵描きアイランド) instead of the standard Pong game. Custom "Modules of choice" should be documented with clear justification._

---

## Individual Contributions

### mfunakos

**Role**: PM, Developer — プロジェクトの進行、進捗管理

**Features & Modules Implemented**:

- **Email/Password Authentication**: Implemented registration (`POST /register`) and login (`POST /login`) with bcrypt password hashing. Zod validation for request bodies. Duplicate email/name checks on registration. Auto-login after successful registration via session creation and cookie. Frontend: `AccountRegister.tsx`, `Login.tsx`, `authApi.ts`, `AuthProvider`, `RequireAuth`, `RequireGuest`.

- **Google OAuth**: Implemented OAuth 2.0 flow with Google. Backend: `googleAuth` (redirect to Google), `googleCallback` (exchange code for user info), `handleGoogleLogin`, `handleGoogleRegister`. State stored in httpOnly cookie for CSRF protection. Handles existing users (email conflict, account not found). `UserAuthentication` model links OAuth providers. Frontend: `GoogleAccountLogin`, `GoogleAccountRegister`, `RedirectLogin`, `SetupProfile` (post-OAuth profile setup).

- **Password Reset (UI)**: Added routes and placeholder pages for password reset flow (`/password-reset/send-mail`, `/password-reset`). Backend email sending not yet implemented.

**Challenges & Solutions**:

- **OAuth state validation**: Used httpOnly cookie to store OAuth state (nonce + mode) to prevent CSRF; validated state on callback and cleared after use.
- **Origin validation**: `isAllowedOrigin` restricts OAuth redirect URIs to configured frontend origins (localhost, ngrok).

### yohatana

**Role**: PO, Developer — 全体統括、意思決定

**Features & Modules Implemented**:

- **Profile, Ranking & Badges**: Implemented profile API (`GET /profile`) returning user name, avatar, total_score, first_place_count, play_count, badges, user_rank, and top_ranker (leaderboard). Backend: `userController.getProfile`, Badge/UserBadge models. Frontend: `Profile.tsx` (profile page with stats, badges grid, leaderboard), `BadgeImage` component, `userApi`, `profileData` types.

- **Terms of Service & Privacy Policy**: Implemented static legal pages. Frontend: `TermsOfService.tsx`, `PrivacyPolicy.tsx`, `TermsOfServiceContent`, `PrivacyPolicyContent`, routes `/terms` and `/privacy-policy`. Footer links to both pages.

- **Gamification System**: Badge model and UserBadge many-to-many relation. Badges seeded (e.g. first win, happy player, rich score). Profile displays earned badges. Score and play statistics updated in `roomManager.finalizeGame` (integrated with game flow). Ranking computed by `total_score` DESC.

**Challenges & Solutions**:

- **Ranking calculation**: Used `prisma.user.count` with `where: { total_score: { gt: user.total_score } }` to compute user rank without loading all users.

### keishii

**Role**: Tech Lead, Developer — 技術選定、開発支援

**Features & Modules Implemented**:

- **Game Modes (DEFAULT, ONE_STROKE)**: ONE_STROKE mode restricts the drawer to a single stroke per turn; `Canvas.tsx` uses `isStrokeDone` to lock drawing until the next round. In ONE_STROKE, clearing the canvas requires starting a new stroke. Game mode passed from room to Canvas and affects drawing behavior.

- **Real-time Drawing & Chat**: WebSocket-based architecture. Backend: `connectionHandler` (JOIN, DRAW, DRAW_END, CLEAR, CHAT, ROUND_START, ROUND_END, TIMER), `chatHandler` (correct-answer detection, score updates, word replacement), `timerManager` (per-room countdown), `roomManager` (broadcast, scores, round state). Frontend: `wsClient`, `Game.tsx` (WebSocket connect, message handling), `Canvas.tsx` (draw events over WebSocket), `ChatMessages`, `ChatInput`, `Timer`, `ScoreBoard`.

- **Complete Game Flow**: Round lifecycle (ROUND_START → word selection, drawer/guesser roles, correct-answer handling → ROUND_END → RESULT). `wordSelector` for random words. `saveScoresToDB`, `endRound`, `finalizeGame` for persistence. Frontend: `Prepare`, `Game`, `Result` pages.

**Challenges & Solutions**:

- **ONE_STROKE UX**: On mouse up, `setIsStrokeDone(true)` locks the canvas; next stroke clears and sends CLEAR to sync all clients.
- **Correct-answer race**: Chat handler uses `round.updateMany` with `word` in `where` to avoid double-processing when multiple guesses arrive.

### kmoriyam

**Role**: Tech Lead, Developer — 技術選定、開発支援

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

[TODO: List any known limitations, bugs, or areas for future improvement.]
There was a discussion regarding how to handle data types sent from the backend to the frontend. Currently, when retrieved data does not exist, it is returned as an HTTP response error. The question arose as to whether this was appropriate, since the absence of data is not truly an error — perhaps simply displaying a message would suffice. Ultimately, the team decided to go with outputting the handled content as a unified approach.

### License

This project is part of the 42 curriculum. See your school's guidelines for usage and distribution.

### Credits

- 42 Common Core – ft_transcendence project
- Technologies: React, Fastify, Prisma, PostgreSQL, and others listed in Technical Stack
