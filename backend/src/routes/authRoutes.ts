import { FastifyInstance } from 'fastify';
import { registerUser } from '../controllers/auth/registerController';
import { me } from '../controllers/auth/meController';

export async function authRoutes(fastify: FastifyInstance) {
	fastify.post('/register', registerUser);
	fastify.get('/me', me);
}
