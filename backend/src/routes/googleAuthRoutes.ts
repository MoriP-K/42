import { FastifyInstance } from "fastify";
import { googleCallback } from "../controllers/auth/googleCallbackController";

export async function googleAuthRoutes(fastify: FastifyInstance) {
	fastify.get("/google/callback", googleCallback);
}
