/**
 * リクエストボディのJSON Schema
 */
export const registerBodySchema = {
	type: 'object',
	required: ['username', 'email', 'password'],
	properties: {
		username: {
			type: 'string',
			minLength: 1
		},
		email: {
			type: 'string',
			format: 'email'
		},
		password: {
			type: 'string',
			minLength: 8
		}
	}
};

export const registerSchema = {
	body: registerBodySchema
};
