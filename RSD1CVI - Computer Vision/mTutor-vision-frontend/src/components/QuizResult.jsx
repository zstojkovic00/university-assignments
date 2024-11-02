import React from 'react';

const QuizResult = ({result, retry}) => {
    return (
        <div className="result-screen">
            <h2>Result: {result.percentage}%</h2>
            <h2>Result: {result.correct} correct options out of {result.total} questions.</h2>
            <button onClick={retry}>Retry</button>

        </div>
    );
};

export default QuizResult;