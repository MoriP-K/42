import { FastifyInstance } from "fastify";
import { registerUser } from "../controllers/auth/registerController";
import { login } from "../controllers/auth/loginController";
import { me } from "../controllers/auth/meController";

export async function authRoutes(fastify: FastifyInstance) {
	fastify.post("/register", registerUser);
	fastify.post("/login", login);
	fastify.get("/me", me);
}
