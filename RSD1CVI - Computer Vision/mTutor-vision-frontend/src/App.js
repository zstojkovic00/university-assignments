import React, {useEffect, useRef, useState} from "react";
import io from 'socket.io-client';
import QuizScreen from './components/QuizScreen.jsx';
import JoinScreen from './components/JoinScreen.jsx';
import Navbar from "./components/Navbar";
import Webcam from "react-webcam";

const socket = io("http://localhost:5000");

function App() {
    const webcamRef = useRef(null);
    const [isQuizStarted, setIsQuizStarted] = useState(false);
    const [currentAnswer, setCurrentAnswer] = useState(null);
    const [currentQuestionIndex, setCurrentQuestionIndex] = useState(0);

    useEffect(() => {
        socket.on('answer', (data) => {
            console.log('Answer from server:', data.answer);
            if (data.answer !== null) {
                setCurrentAnswer(data.answer);
            }
        });

        socket.on('thumb_up', (data) => {
            console.log('Thumb up from server:', data.status);
            if (data.status === 'Thumb is up!') {
                setCurrentAnswer("thumb_up");
            }
        });

        return () => {
            socket.off('answer');
            socket.off('thumb_up');
        };
    }, []);

    const gotoNextQuestion = () => {
        setCurrentQuestionIndex(currentQuestionIndex => currentQuestionIndex + 1);
        setCurrentAnswer(null);
    };

    const captureFrame = () => {
        const imageSrc = webcamRef.current.getScreenshot();
        if (imageSrc) {
            socket.emit('process_frame', {image: imageSrc});
        }
    };

    useEffect(() => {
        let interval;
        if (isQuizStarted) {
            interval = setInterval(captureFrame, 1000);
        }
        return () => clearInterval(interval);
    }, [isQuizStarted]);

    return (
        <div className="App">
            <Navbar/>
            <div className="quiz-container">
                {
                    isQuizStarted ? (
                        <>
                            <QuizScreen
                                retry={() => {
                                    setIsQuizStarted(false);
                                    setCurrentAnswer(null);
                                    setCurrentQuestionIndex(0);
                                }}
                                currentAnswer={currentAnswer}
                                currentQuestionIndex={currentQuestionIndex}
                                gotoNextQuestion={gotoNextQuestion}
                            />

                            <div className="webcam-container">
                                <Webcam
                                    audio={false}
                                    ref={webcamRef}
                                    screenshotFormat="image/jpeg"
                                    width={320}
                                    height={240}
                                    mirrored={true}
                                />
                            </div>
                        </>
                    ) : (
                        <JoinScreen start={() => setIsQuizStarted(true)}/>
                    )
                }
            </div>
        </div>
    );
}

export default App;
