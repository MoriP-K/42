export type RegisterFormField =
	| "name"
	| "email"
	| "password"
	| "passwordConfirm";

export type RegisterFormValues = {
	name: string;
	email: string;
	password: string;
	passwordConfirm: string;
};
