import { useEffect } from 'react';
import { userApi } from '../api/userApi'
import { ApiError } from '../api/apiClient'


import Footer from "../components/Footer"

const Login = () => {
	useEffect(() => {
		const run = async () => {
			try {
				const me = await userApi.getMe()
				console.log('me:', me)
			} catch (e) {
				if (e instanceof ApiError) {
					console.error('API Error', {
						status: e.status,
						data: e.data, // 例: { message: "Unauthorized" }
					})
				} else {
					console.error('Unknown Error', e)
				}
			}
		}

		run()
	}, []);
	return (
		<div>
			<Footer></Footer>
		</div>
	)
}

export default Login
