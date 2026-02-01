import { useCallback, useEffect, useMemo, useState, type ReactNode } from 'react'
import { ApiError } from '../../api/apiClient'
import { userApi } from '../../api/userApi'
import { AuthContext, type AuthContextValue } from './authContext'

export function AuthProvider({ children }: { children: ReactNode }) {
	const [isAuthenticated, setIsAuthenticated] = useState(false)

	const refreshAuth = useCallback(async () => {
		try {
			await userApi.me()
			setIsAuthenticated(true)
			return true
		} catch (err) {
			// 401 を含む失敗は未ログイン扱いに倒す（ログ出力はしない）
			if (err instanceof ApiError && err.status === 401) {
				setIsAuthenticated(false)
				return false
			}
			setIsAuthenticated(false)
			return false
		}
	}, [])

	useEffect(() => {
		// 起動時に一度だけ /api/me で状態を温める（UIはブロックしない）
		const t = setTimeout(() => {
			void refreshAuth()
		}, 0)
		return () => clearTimeout(t)
	}, [refreshAuth])

	const value = useMemo<AuthContextValue>(() => ({ isAuthenticated, refreshAuth }), [isAuthenticated, refreshAuth])

	return <AuthContext.Provider value={value}>{children}</AuthContext.Provider>
}
