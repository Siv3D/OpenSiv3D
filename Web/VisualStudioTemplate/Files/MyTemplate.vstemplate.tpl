<VSTemplate Version="3.0.0" xmlns="http://schemas.microsoft.com/developer/vstemplate/2005" Type="Project">
  <TemplateData>
    <Name>OpenSiv3D(0.6.4)Web</Name>
    <Description>A project for creating a Siv3D application</Description>
    <ProjectType>VC</ProjectType>
    <LanguageTag>cpp</LanguageTag>
    <ProjectTypeTag>games</ProjectTypeTag>
    <ProjectSubType>
    </ProjectSubType>
    <SortOrder>1000</SortOrder>
    <CreateNewFolder>true</CreateNewFolder>
    <DefaultName>OpenSiv3Dv0_6ForWeb</DefaultName>
    <ProvideDefaultName>true</ProvideDefaultName>
    <LocationField>Enabled</LocationField>
    <EnableLocationBrowseButton>true</EnableLocationBrowseButton>
    <Icon>__TemplateIcon.ico</Icon>
    <PreviewImage>__PreviewImage.png</PreviewImage>
  </TemplateData>
  <TemplateContent>
    <Project TargetFileName="Siv3DTest.vcxproj" File="Siv3DTest.vcxproj" ReplaceParameters="true">
      <ProjectItem ReplaceParameters="false" TargetFileName="$projectname$.vcxproj.filters">Siv3DTest.vcxproj.filters</ProjectItem>
      <ProjectItem ReplaceParameters="false" TargetFileName="Main.cpp" OpenInEditor="true">Main.cpp</ProjectItem>
${Items}
      <ProjectItem ReplaceParameters="false" TargetFileName="web-player.html">Templates\Embeddable\web-player.html</ProjectItem>
      <ProjectItem ReplaceParameters="false" TargetFileName="web-player.js">Templates\Embeddable\web-player.js</ProjectItem>
    </Project>
  </TemplateContent>
</VSTemplate>