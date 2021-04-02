import React from 'react';
import {
  ServicesContainer,
  ServicesH1,
  ServicesWrapper,
  ServicesCard,
  ServicesIcon,
  ServicesH2,
  ServicesP
} from './ServicesElements';

const Services = () => {
  return (
    <ServicesContainer id='services'>
      <ServicesH1>Technologies</ServicesH1>
      <ServicesWrapper>
        <ServicesCard>
          <ServicesIcon/>
          <ServicesH2>Systems</ServicesH2>
          <ServicesP>
            Linux OS (Ubuntu & Linux Redhat), npm, Version Control (Git),
            Code Repositories (Github & Jira), bitbucket, Automated Builds and Deployments (Travis CI & Jenkins)
          </ServicesP>
        </ServicesCard>
        <ServicesCard>
          <ServicesIcon/>
          <ServicesH2>Programming Languages</ServicesH2>
          <ServicesP>
            C,
            C++,
            Java,
            Python,
            SQL,
            ReactJS,
            Groovy
          </ServicesP>
        </ServicesCard>
        <ServicesCard>
          <ServicesIcon/>
          <ServicesH2>Skills</ServicesH2>
          <ServicesP>
            Continuous Integration, Programming, Software Engineering, Networking, Security, 
            Test Driven Development, Agile Development, Kanban boards, Scrum, 
          </ServicesP>
        </ServicesCard>
      </ServicesWrapper>
    </ServicesContainer>
  );
};

export default Services;
