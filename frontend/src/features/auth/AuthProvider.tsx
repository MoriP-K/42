import { useCallback, useEffect, useMemo, useState, type ReactNode } from 'react'
import { authApi } from '../../api/authApi'
import { AuthContext, type AuthContextValue } from './authContext'

export function AuthProvider({ children }: { children: ReactNode }) {
	const [isAuthenticated, setIsAuthenticated] = useState(false)

	const refreshAuth = useCallback(async () => {
		try {
			await authApi.me()
			setIsAuthenticated(true)
			return true
		} catch {
			// 401 を含む失敗は未ログイン扱い
			setIsAuthenticated(false)
			return false
		}
	}, [])

	useEffect(() => {
		// 起動時に一度だけ /api/me でログイン状態を取得する
		const t = setTimeout(() => {
			void refreshAuth()
		}, 0)
		return () => clearTimeout(t)
	}, [refreshAuth])

	const value = useMemo<AuthContextValue>(() => ({ isAuthenticated, refreshAuth }), [isAuthenticated, refreshAuth])

	return <AuthContext.Provider value={value}>{children}</AuthContext.Provider>
}
