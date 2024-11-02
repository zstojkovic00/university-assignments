import React, {useEffect, useRef, useState} from 'react';

const Question = ({question, totalQuestions, currentQuestion, setAnswer, currentAnswer, gotoNextQuestion }) => {
    const [selectedOption, setSelectedOption] = useState(null);
    const timer = useRef(null);
    const progressBar = useRef(null);

    function handleNextQuestion() {
        if (timer.current) {
            clearTimeout(timer.current);
        }
        if (selectedOption !== null) {
            setAnswer(selectedOption);
        }
        setSelectedOption(null);
        gotoNextQuestion();
    }

    useEffect(() => {
        if (currentAnswer !== null) {
            setSelectedOption(currentAnswer);
        }
    }, [currentAnswer]);

    useEffect(() => {
        if (progressBar.current) {
            progressBar.current.classList.remove('active');
            void progressBar.current.offsetWidth;
            progressBar.current.classList.add('active');
        }
        timer.current = setTimeout(handleNextQuestion, 10 * 1000);
        return () => {
            if (timer.current) {
                clearTimeout(timer.current);
            }
        };
    }, [question]);

    return (
        <div className="question">
            <div className="progress-bar" ref={progressBar}></div>
            <div className="question-count">
                <b> {currentQuestion}</b>
                of
                <b> {totalQuestions}</b>
            </div>
            <div className="main">
                <div className="title">
                    <span> Question:</span>
                    <p>{question.title}</p>
                </div>
                <div className="options">
                    {
                        question.options.map((option, index) => {
                            return (
                                <div className={index === selectedOption ? "option active" : "option"}
                                     key={index}
                                     onClick={() => setSelectedOption(index)}
                                >
                                    {option}
                                </div>
                            );
                        })
                    }
                </div>
            </div>
            <div className="control">
                <button onClick={handleNextQuestion}>Next</button>
            </div>
        </div>
    );
};

export default Question;
