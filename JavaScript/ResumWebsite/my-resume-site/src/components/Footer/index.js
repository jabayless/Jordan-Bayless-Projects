import React from 'react';
import {
  FaFacebook,
  FaInstagram,
  FaYoutube,
  FaTwitter,
  FaLinkedin
} from 'react-icons/fa';
import { animateScroll as scroll } from 'react-scroll';
import {
  FooterContainer,
  FooterWrap,
  FooterLinksContainer,
  FooterLinksWrapper,
  FooterLinkItems,
  FooterLinkTitle,
  FooterLink,
  SocialMedia,
  SocialMediaWrap,
  SocialLogo,
  WebsiteRights,
  SocialIcons,
  SocialIconLink
} from './FooterElements';

const Footer = () => {
  const toggleHome = () => {
    scroll.scrollToTop();
  };
  return (
    <FooterContainer>
      <FooterWrap>
        <FooterLinksContainer>
          <FooterLinksWrapper>
            <FooterLinkItems>
              <FooterLinkTitle>More About Me</FooterLinkTitle>
              <FooterLink to='/sign-up'>My Blog</FooterLink>
            </FooterLinkItems>
            <FooterLinkItems>
              <FooterLinkTitle></FooterLinkTitle>
            </FooterLinkItems>
            <FooterLinkItems>
              <FooterLinkTitle>Contact Me</FooterLinkTitle>
              <FooterLink to='/'>Phone:</FooterLink>
              <FooterLink to='/'>(719)-304-1192</FooterLink>
              <FooterLink to='/'>Gmail:</FooterLink>
              <FooterLink to='/'>jordanbayless6@gmail.com</FooterLink>
              <FooterLink to='/'>Linkedin:</FooterLink>
              <FooterLink to='/'>''</FooterLink>
              <FooterLink to='/'>Github</FooterLink>
              <FooterLink to='/'>jabayless</FooterLink>
            </FooterLinkItems>
            <FooterLinkItems>
              <FooterLinkTitle></FooterLinkTitle>
            </FooterLinkItems>
          </FooterLinksWrapper>
          <FooterLinksWrapper>
            <FooterLinkItems>
              <FooterLinkTitle>Social Media</FooterLinkTitle>
              <FooterLink to='/'>Instagram</FooterLink>
              <FooterLink to='/'>Facebook</FooterLink>
              <FooterLink to='/'>Youtube</FooterLink>
              <FooterLink to='/'>Twitter</FooterLink>
            </FooterLinkItems>
          </FooterLinksWrapper>
        </FooterLinksContainer>
        <SocialMedia>
          <SocialMediaWrap>
            <SocialLogo to='/' onClick={toggleHome}>
              Thanks For Visiting
            </SocialLogo>
            <SocialIcons>
              <SocialIconLink href='/' target='_blank' aria-label='Facebook'>
                <FaFacebook />
              </SocialIconLink>
              <SocialIconLink href='/' target='_blank' aria-label='Instagram'>
                <FaInstagram />
              </SocialIconLink>
              <SocialIconLink
                href='//www.youtube.com/channel/UCsKsymTY_4BYR-wytLjex7A?view_as=subscriber'
                target='_blank'
                aria-label='Youtube'
                rel='noopener noreferrer'
              >
                <FaYoutube />
              </SocialIconLink>
              <SocialIconLink
                target='_blank'
                aria-label='Twitter'
                href='//www.twitter.com/briandesignz'
              >
                <FaTwitter />
              </SocialIconLink>
              <SocialIconLink href='/' target='_blank' aria-label='Linkedin'>
                <FaLinkedin />
              </SocialIconLink>
            </SocialIcons>
          </SocialMediaWrap>
        </SocialMedia>
      </FooterWrap>
    </FooterContainer>
  );
};

export default Footer;