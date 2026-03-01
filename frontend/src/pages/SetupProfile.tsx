import React, { useState } from "react";
import { useNavigate, useLocation, type Location } from "react-router-dom";
import { authApi } from "../api/authApi";
import { ApiError } from "../api/apiClient";
import { useAuth } from "../features/auth/useAuth";
import Footer from "../components/footer/Footer";
import { AuthFormShell } from "../components/auth/AuthFormShell";
import { AuthTextField } from "../components/auth/AuthTextField";

type SetupProfileLocationState = {
	from?: Location;
	reason?: "profile_incomplete";
};

const SetupProfile = () => {
	const navigate = useNavigate();
	const location = useLocation();
	const { refreshAuth } = useAuth();
	const [name, setName] = useState("");
	const [fieldError, setFieldError] = useState<string | null>(null);
	const [serverError, setServerError] = useState<string | null>(null);

	const from = (location.state as SetupProfileLocationState)?.from;
	const isRedirectedForIncomplete =
		(location.state as SetupProfileLocationState)?.reason ===
		"profile_incomplete";

	const normalizeErrResponse = (err: unknown) => {
		if (!(err instanceof ApiError)) {
			return err instanceof Error
				? err.message
				: "予期しないエラーが発生しました";
		}
		const body =
			typeof err.data === "object" && err.data !== null
				? (err.data as { field?: unknown; message?: unknown })
				: null;
		const message = typeof body?.message === "string" ? body.message : null;
		return message ?? "予期しないエラーが発生しました";
	};

	const handleSubmit = async (e: React.FormEvent) => {
		e.preventDefault();
		setServerError(null);
		setFieldError(null);

		const trimmed = name.trim();
		if (!trimmed) {
			setFieldError("ユーザー名を入力してください");
			return;
		} else if (!/^[a-z0-9_]+$/.test(trimmed)) {
			setFieldError("ユーザー名には半角英数字と「_」のみ使用できます");
			return;
		}

		try {
			await authApi.updateMe({ name: trimmed });
			const ok = await refreshAuth();
			if (!ok) {
				setServerError("更新に失敗しました。再度お試しください。");
				return;
			}
			navigate(from ?? "/", { replace: true });
		} catch (err) {
			setServerError(normalizeErrResponse(err));
		}
	};

	return (
		<>
			<div className="text-center mb-4">
				<span className="text-2xl font-bold">プロフィール設定</span>
			</div>
			{isRedirectedForIncomplete && (
				<p className="text-center text-base-content/80 mb-4 text-error">
					ユーザー名が未設定のため、設定してください。
				</p>
			)}

			<AuthFormShell
				serverError={serverError}
				onSubmit={handleSubmit}
				actions={
					<button type="submit" className="btn btn-primary w-full">
						登録する
					</button>
				}
			>
				<AuthTextField
					label="ユーザー名"
					htmlFor="name"
					description="半角英字、数字、_を使用できます。"
					error={fieldError ?? undefined}
					inputProps={{
						id: "name",
						type: "text",
						name: "name",
						autoComplete: "name",
						value: name,
						onChange: e => setName(e.target.value),
						placeholder: "ユーザー名を入力",
					}}
				/>
			</AuthFormShell>

			<Footer />
		</>
	);
};

export default SetupProfile;
