_This project has been created as part of the 42 curriculum by nfunakos, yohatana, ken, kmoriyam._

# Oekaki no Mori (おえかきの森)

## Description

**Oekaki no Mori** (おえかきの森) is a real-time online drawing guessing game built as the final project of the 42 Common Core curriculum. Players create or join game rooms, take turns drawing prompts while others guess the word, and compete for high scores.

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
    - `VITE_API_URL` – Backend API URL for the frontend (default: `http://localhost:3000`)
    - For Google OAuth: `GOOGLE_CLIENT_ID`, `GOOGLE_CLIENT_SECRET`, `GOOGLE_REDIRECT_URI`, `FRONTEND_URL`

### Running the Project

1. Start all services with Docker Compose:

    ```bash
    docker compose up -d
    ```

2. Access the application:
    - **Frontend**: http://localhost:5173
    - **Backend API**: http://localhost:3000
    - **Database**: localhost:5432 (PostgreSQL)

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

| Member   | Assigned Role(s)                          | Responsibilities          |
| -------- | ----------------------------------------- | ------------------------- |
| nfunakos | [TODO: e.g. PO, PM, Tech Lead, Developer] | [TODO: Brief description] |
| yohatana | [TODO: e.g. PO, PM, Tech Lead, Developer] | [TODO: Brief description] |
| ken      | [TODO: e.g. PO, PM, Tech Lead, Developer] | [TODO: Brief description] |
| kmoriyam | [TODO: e.g. PO, PM, Tech Lead, Developer] | [TODO: Brief description] |

---

## Project Management

### Work Organization

[TODO: Describe how the team organized the work: task distribution, meeting schedule, sprint structure, etc.]

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
| Game Modes (DEFAULT, ONE_STROKE)  | ken            | Two play modes: standard drawing and single-stroke challenge   |
| Real-time Drawing & Chat          | ken            | WebSocket-based canvas, chat messages, timer, scoreboard       |
| Profile, Ranking & Badges         | yohatana       | User profile, avatar, badges, total score, play count, ranking |
| Terms of Service & Privacy Policy | yohatana       | Static legal pages                                             |

---

## Modules

[TODO: List all chosen modules (Major and Minor) from the 42 ft_transcendence subject. Include point calculation (Major = 2pts, Minor = 1pt), justification for each module choice, implementation overview, and which team member(s) worked on each module.]

### Module Summary Template

| Module Name | Type (Major/Minor) | Points | Justification | Implemented By |
| ----------- | ------------------ | ------ | ------------- | -------------- |
| [TODO]      | Major              | 2      | [TODO]        | [TODO]         |
| [TODO]      | Minor              | 1      | [TODO]        | [TODO]         |

_Note: This project implements a drawing guessing game (おえかきの森) instead of the standard Pong game. Custom "Modules of choice" should be documented with clear justification._

---

## Individual Contributions

### nfunakos

[TODO: Detailed breakdown of contributions. Specific features, modules, or components implemented. Challenges faced and how they were overcome.]

### yohatana

[TODO: Detailed breakdown of contributions. Specific features, modules, or components implemented. Challenges faced and how they were overcome.]

### ken

[TODO: Detailed breakdown of contributions. Specific features, modules, or components implemented. Challenges faced and how they were overcome.]

### kmoriyam

[TODO: Detailed breakdown of contributions. Specific features, modules, or components implemented. Challenges faced and how they were overcome.]

---

## Additional Information

### Known Limitations

[TODO: List any known limitations, bugs, or areas for future improvement.]

### License

This project is part of the 42 curriculum. See your school's guidelines for usage and distribution.

### Credits

- 42 Common Core – ft_transcendence project
- Technologies: React, Fastify, Prisma, PostgreSQL, and others listed in Technical Stack
