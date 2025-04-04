pipeline
{
    agent any
    stages
    {
        stage('Build')
        {
            steps
            {
                echo "Building project in container..."
                sh '''docker build -t my_builder_image -f Dockerfile.build .'''
            }
        }
        stage('Test')
        {
            steps
            {
                echo "Running tests..."
                sh '''docker run --name my_test_run --rm my_builder_image ./fruit_test'''
            }
        }
        stage('Archive logs') 
        {
            steps 
            {
                echo "Archivizing logs..."
                archiveArtifacts artifacts: 'logs/*.log', fingerprint: true
            }
        }
    }
}
