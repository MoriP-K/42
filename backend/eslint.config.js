import js from "@eslint/js";
import globals from "globals";
import tseslint from "typescript-eslint";
import nodePlugin from "eslint-plugin-n";
import prettierConfig from "eslint-config-prettier";

export default tseslint.config(
	{ ignores: ["dist", "node_modules", "prisma"] },
	{
		extends: [
			js.configs.recommended,
			...tseslint.configs.recommended,
			nodePlugin.configs["flat/recommended-script"],
		],
		files: ["**/*.ts"],
		languageOptions: {
			ecmaVersion: 2024,
			globals: globals.node,
		},
		rules: {
			// --- プロジェクト固有の規約 ---
			"@typescript-eslint/naming-convention": [
				"error",
				{ selector: "variable", format: ["camelCase", "UPPER_CASE"] },
				{ selector: "function", format: ["camelCase"] },
				{ selector: "typeLike", format: ["PascalCase"] },
			],

			// Node.js固有設定
			"n/no-missing-import": "off", // TypeScriptのパス解決と競合するためoff
			"@typescript-eslint/no-unused-vars": [
				"error",
				{ argsIgnorePattern: "^_" },
			],
			"no-unused-expressions": "error",
		},
	},
	prettierConfig,
);
