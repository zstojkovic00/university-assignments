import React from 'react';
import hand from '../data/hand-robot.png'
const JoinScreen = ({ start }) => {
    return (
        <div className="join-screen">
            <div className="image-container">
                <div className="text-container">
                    <p className="intro">Simply raise your fingers to select an answer:</p>
                    <p className="options">
                        1 finger for option A
                        <br/>2 fingers for option B
                        <br/>3 fingers for option C
                        <br/>4 fingers for option D.
                    </p>
                </div>
                <img src={hand} alt="Hand" className="hand-image"/>
            </div>
            <h2>Join Quiz</h2>
            <button onClick={start}>Start</button>
        </div>
    );
};

export default JoinScreen;