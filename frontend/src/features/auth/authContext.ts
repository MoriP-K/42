import { createContext } from 'react'

export type AuthContextValue = {
	isAuthenticated: boolean
	refreshAuth: () => Promise<boolean>
}

export const AuthContext = createContext<AuthContextValue | null>(null)

