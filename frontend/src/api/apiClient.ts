const BASE_URL = 'http://localhost:3000/api';

/**
 * 共通のAPIクライアント
 * fetchをラップして共通の処理（エラーハンドリング等）を行う
 */
export const apiClient = async (endpoint: string, options: RequestInit = {}) => {
    const url = `${BASE_URL}${endpoint}`;
    
    // 必要に応じてヘッダーを追加
    const headers = {
        'Content-Type': 'application/json',
        ...options.headers,
    };

    const response = await fetch(url, { ...options, headers });

    if (!response.ok) {
        // ここで共通のエラーハンドリングが可能（LaravelのAxios Interceptor相当）
        const error = await response.json().catch(() => ({}));
        throw new Error(error.message || 'API Request Failed');
    }

    return response.json();
};
