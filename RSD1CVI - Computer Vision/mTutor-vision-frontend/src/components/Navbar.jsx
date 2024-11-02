import React from 'react';
import logo from '../data/mtutor-vision-logo.png'

const Navbar = () => {
    return (
        <div className="navbar">
            <div className="logo">
                <img src={logo} alt="mTutor Vision"/>
            </div>
        </div>
    );
};

export default Navbar;