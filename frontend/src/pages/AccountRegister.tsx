import Footer from "../components/footer/Footer";
import React, { useState } from "react";
import { authApi } from "../api/authApi";
import { ApiError } from "../api/apiClient";
import { AuthFormShell } from "../components/auth/AuthFormShell";
import { AuthTextField } from "../components/auth/AuthTextField";
import BackButton from "../components/BackButton";
import { useNavigate } from "react-router-dom";
import { z } from "zod";
import type { RegisterFormField, RegisterFormValues } from "../types/auth";

type RegisterError =
	| { type: "server"; message: string }
	| { type: "unknown"; message: string };

const NameSchema = z
	.string()
	.trim()
	.min(1, "ユーザー名を入力してください")
	.regex(/^[A-Za-z0-9_]+$/, "ユーザー名は半角英数字と_のみ使用できます");

const EmailSchema = z
	.string()
	.trim()
	.min(1, "メールアドレスを入力してください")
	.email("メールアドレスの形式が正しくありません");

const PasswordSchema = z
	.string()
	.trim()
	.min(1, "パスワードを入力してください")
	.min(8, "パスワードは8文字以上で入力してください")
	.regex(
		/^(?=.*[A-Z])(?=.*[a-z])(?=.*\d)[A-Za-z0-9]{8,}$/,
		"パスワードには英大文字・英小文字・数字をそれぞれ1文字以上含めてください",
	);

const PasswordConfirmSchema = z
	.string()
	.trim()
	.min(1, "パスワード確認を入力してください");

const RegisterFormSchema = z
	.object({
		name: NameSchema,
		email: EmailSchema,
		password: PasswordSchema,
		passwordConfirm: PasswordConfirmSchema,
	})
	.superRefine(({ password, passwordConfirm }, ctx) => {
		if (password !== passwordConfirm) {
			ctx.addIssue({
				code: "custom",
				message: "パスワードが一致しません",
				path: ["passwordConfirm"],
			});
		}
	});

const toFieldErrors = (
	issues: z.ZodIssue[],
): Partial<Record<RegisterFormField, string>> => {
	const next: Partial<Record<RegisterFormField, string>> = {};
	for (const issue of issues) {
		const key = issue.path[0];
		if (
			(key === "name" ||
				key === "email" ||
				key === "password" ||
				key === "passwordConfirm") &&
			next[key] === undefined
		) {
			next[key] = issue.message;
		}
	}
	return next;
};

const AccountRegister = () => {
	const navigate = useNavigate();
	const [name, setName] = useState("");
	const [email, setEmail] = useState("");
	const [password, setPassword] = useState("");
	const [passwordConfirm, setPasswordConfirm] = useState("");

	const [fieldErrors, setFieldErrors] = useState<
		Partial<Record<RegisterFormField, string>>
	>({});
	const [touched, setTouched] = useState<
		Partial<Record<RegisterFormField, boolean>>
	>({});
	const [serverError, setServerError] = useState<string | null>(null);

	const validateAll = (values: RegisterFormValues) => {
		const result = RegisterFormSchema.safeParse(values);
		if (result.success) return {};
		return toFieldErrors(result.error.issues);
	};

	const validateName = (value: string) => {
		const result = NameSchema.safeParse(value);
		if (result.success) return undefined;
		return result.error.issues[0]?.message;
	};

	const validateEmail = (value: string) => {
		const result = EmailSchema.safeParse(value);
		if (result.success) return undefined;
		return result.error.issues[0]?.message;
	};

	const validatePassword = (value: string) => {
		const result = PasswordSchema.safeParse(value);
		if (result.success) return undefined;
		return result.error.issues[0]?.message;
	};

	const validatePasswordConfirm = (
		passwordValue: string,
		confirmValue: string,
	) => {
		const required = PasswordConfirmSchema.safeParse(confirmValue);
		if (!required.success) return required.error.issues[0]?.message;
		if (passwordValue !== confirmValue) return "パスワードが一致しません";
		return undefined;
	};

	const getValues = (
		overrides: Partial<RegisterFormValues> = {},
	): RegisterFormValues => ({
		name,
		email,
		password,
		passwordConfirm,
		...overrides,
	});

	const handleFieldChange = (field: RegisterFormField, value: string) => {
		setTouched(prev => ({ ...prev, [field]: true }));
		if (serverError !== null) setServerError(null);

		switch (field) {
			case "name": {
				setName(value);
				setFieldErrors(prev => ({ ...prev, name: validateName(value) }));
				return;
			}
			case "email": {
				setEmail(value);
				setFieldErrors(prev => ({ ...prev, email: validateEmail(value) }));
				return;
			}
			case "password": {
				setPassword(value);
				setFieldErrors(prev => ({
					...prev,
					password: validatePassword(value),
				}));
				return;
			}
			case "passwordConfirm": {
				setPasswordConfirm(value);
				const values = getValues({ passwordConfirm: value });
				setFieldErrors(prev => ({
					...prev,
					passwordConfirm: validatePasswordConfirm(
						values.password,
						values.passwordConfirm,
					),
				}));
				return;
			}
			default:
				return;
		}
	};

	const normalizeErrResponse = (err: unknown): RegisterError => {
		if (!(err instanceof ApiError)) {
			return {
				type: "unknown",
				message:
					err instanceof Error
						? err.message
						: "予期しないエラーが発生しました",
			};
		}
		const body =
			typeof err.data === "object" && err.data !== null
				? (err.data as { field?: unknown; message?: unknown })
				: null;
		const message = typeof body?.message === "string" ? body.message : null;

		if (message !== null) {
			return {
				type: "unknown",
				message: message,
			};
		}

		return {
			type: "unknown",
			message: "予期しないエラーが発生しました",
		};
	};

	const handleSubmit = async (e: React.FormEvent) => {
		e.preventDefault();
		setServerError(null);
		setTouched({
			name: true,
			email: true,
			password: true,
			passwordConfirm: true,
		});

		const nextErrors = validateAll({
			name,
			email,
			password,
			passwordConfirm,
		});
		setFieldErrors(nextErrors);
		if (Object.keys(nextErrors).length > 0) return;

		try {
			await authApi.register({ name, email, password });
			navigate("/");
		} catch (err) {
			// レスポンスの正規化
			const result = normalizeErrResponse(err);
			setServerError(result.message);
		}
	};

	return (
		<>
			{/* ヘッダー */}
			<div className="text-center mb-4">
				<span className="text-2xl font-bold">アカウント新規作成</span>
			</div>

			{/* 記入フォーム */}
			<AuthFormShell
				serverError={serverError}
				onSubmit={handleSubmit}
				top={
					<>
						<button
							type="button"
							className="btn btn-outline w-full"
						>
							{/* TODO: Googleアカウントで登録処理*/}
							<span className="inline-flex items-center gap-2">
								<span className="i" aria-hidden="true">
									G
								</span>
								Googleアカウントで登録
							</span>
						</button>
						<div className="divider my-0 text-sm text-base-content/60">
							または
						</div>
					</>
				}
				actions={
					<div className="space-y-2">
						<button
							type="submit"
							className="btn btn-primary w-full"
						>
							アカウント作成
						</button>
						<BackButton></BackButton>
					</div>
				}
			>
				<AuthTextField
					label="ユーザー名"
					htmlFor="name"
					description="半角英字、数字、_を使用できます。"
					error={touched.name ? fieldErrors.name : undefined}
					inputProps={{
						id: "name",
						type: "text",
						name: "name",
						placeholder: "例: user_name",
						autoComplete: "username",
						value: name,
						onChange: e => handleFieldChange("name", e.target.value),
					}}
				/>

				<AuthTextField
					label="メールアドレス"
					htmlFor="email"
					error={touched.email ? fieldErrors.email : undefined}
					inputProps={{
						id: "email",
						type: "text",
						name: "email",
						placeholder: "example@example.com",
						autoComplete: "email",
						value: email,
						onChange: e => handleFieldChange("email", e.target.value),
					}}
				/>

				<AuthTextField
					label="パスワード"
					htmlFor="password"
					description="大文字・小文字・数字を組み合わせて8文字以上で入力してください。"
					error={touched.password ? fieldErrors.password : undefined}
					inputProps={{
						id: "password",
						type: "password",
						name: "password",
						autoComplete: "new-password",
						value: password,
						onChange: e => handleFieldChange("password", e.target.value),
					}}
				/>

				<AuthTextField
					label="パスワード確認"
					htmlFor="passwordConfirm"
					error={
						touched.passwordConfirm
							? fieldErrors.passwordConfirm
							: undefined
					}
					inputProps={{
						id: "passwordConfirm",
						type: "password",
						name: "passwordConfirm",
						autoComplete: "new-password",
						value: passwordConfirm,
						onChange: e =>
							handleFieldChange("passwordConfirm", e.target.value),
					}}
				/>
			</AuthFormShell>

			{/* フッター */}
			<Footer />
		</>
	);
};

export default AccountRegister;
