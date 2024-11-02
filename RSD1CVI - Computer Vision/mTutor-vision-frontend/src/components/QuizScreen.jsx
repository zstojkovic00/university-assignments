import React, {useEffect, useState} from 'react';
import QuestionList from '../data/questions.json';
import Question from './Question.jsx';
import QuizResult from './QuizResult.jsx';

const QuizScreen = ({retry, currentAnswer, currentQuestionIndex, gotoNextQuestion}) => {
    const [markedAnswers, setMarkedAnswers] = useState(new Array(QuestionList.length));
    const isQuestionEnd = currentQuestionIndex === QuestionList.length;

    function calculateResult() {
        let correct = 0;
        QuestionList.forEach((question, index) => {
            if (question.correctOptionIndex === markedAnswers[index]) {
                correct++;
            }
        });
        return {
            total: QuestionList.length,
            correct: correct,
            percentage: Math.trunc((correct / QuestionList.length) * 100)
        };
    }

    const handleSetAnswer = (index) => {
        setMarkedAnswers((arr) => {
            let newArr = [...arr];
            newArr[currentQuestionIndex] = index;
            return newArr;
        });
    };

    useEffect(() => {
        if (currentAnswer !== null) {
            handleSetAnswer(currentAnswer);
        }
    }, [currentAnswer]);

    return (
        <div className="quiz-screen">
            {
                isQuestionEnd ? (
                    <QuizResult
                        result={calculateResult()}
                        retry={retry}
                    />
                ) : (
                    <Question
                        question={QuestionList[currentQuestionIndex]}
                        totalQuestions={QuestionList.length}
                        currentQuestion={currentQuestionIndex + 1}
                        setAnswer={handleSetAnswer}
                        currentAnswer={currentAnswer}
                        gotoNextQuestion={gotoNextQuestion}
                    />
                )
            }
        </div>
    );
};

export default QuizScreen;
